#include "soundSensor.h"

#include <HardwareSerial.h>
#include <t-beam/utilities.h>
#include <driver/i2s.h>

#include <Logger.hpp>

#include "data.pb.h"


#define bufferLen 64
int16_t sBuffer[bufferLen];

float mean = 0;
Data sound_message = Data_init_zero;

Data readSoundSensorData() {

  // Start I2S
  i2s_start(I2S_PORT);

  // Get I2S data and place in data buffer
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK)
  {
    // Read I2S data buffer
    int16_t samples_read = bytesIn / 8;
    if (samples_read > 0) {
      mean = 0;
      for (int16_t i = 0; i < samples_read; ++i) {
        mean += (sBuffer[i]);
      }
      // Average the data reading
      mean /= samples_read;

      // TODO: remove print
      Serial.println(mean);
    }
  }

  // Stop I2S_PORT
  i2s_stop(I2S_PORT);
  // TODO: Find out when to uninstall drivers

  // Create and return the message to transfert via loRa protocole
  sound_message.sensor_pin = SOUND_SENSOR_COM_PIN;
  strcpy(sound_message.sensor_id, SENSOR_COM_ID);
  sound_message.values_count = 1;
  strcpy(sound_message.values[0].value_type, SOUND_SENSOR_COM_TYPE);
  snprintf(sound_message.values[0].value, sizeof(sound_message.values[0].value), "%.2f", mean);
  return sound_message;
}

void setupSoundSensor() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0,
    .mclk_multiple = I2S_MCLK_MULTIPLE_DEFAULT,
    .bits_per_chan = I2S_BITS_PER_CHAN_DEFAULT
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  // Set I2S pin configuration
  const i2s_pin_config_t pin_config = {
    .mck_io_num = I2S_PIN_NO_CHANGE,
    .bck_io_num = SOUND_I2S_SCK,
    .ws_io_num = SOUND_I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = SOUND_I2S_SD
  };
  
  i2s_set_pin(I2S_PORT, &pin_config);
 }