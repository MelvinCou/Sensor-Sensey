#include "loRaHandler.h"

#include <LoRa.h>
#include <pb_encode.h>
#include <webConfigurer.h>

#include <Logger.hpp>

#include "data.pb.h"
#include "t-beam/utilities.h"

void LoRaHandler::loRaBegin(WebConfigurer& conf) {
  LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
  if (!LoRa.begin(conf.getLoraRadioFreq())) {
    LOG_ERROR("Starting LoRa failed!\n");
  }
  LoRa.setSignalBandwidth(conf.getLoraRadioBw() * 1000);
  LoRa.setSyncWord(0xAB);
  LoRa.setSpreadingFactor(7);
  LoRa.setPreambleLength(8);
  /*
  LoRa.setTxPower(CONFIG_RADIO_OUTPUT_POWER);
  LoRa.disableCrc();
  LoRa.disableInvertIQ();
  LoRa.setCodingRate4(7);
  */
}

Data data = Data_init_default;
uint8_t buffer[Data_size];
pb_ostream_t ostream;
#define MAX_VALUES sizeof(data.values) / sizeof(data.values[0])

void LoRaHandler::addValueToSend(const Sensor& sensor, const char* sensorCommunityId, uint32_t sensorPin) {
  const size_t& size = sensor.getValuesCount();
  if (size + data.values_count > MAX_VALUES) {
    LOG_ERROR("Overflow of values : %d (size) + %d (values_count) > %d (MAX_VALUES)\n", size, data.values_count, MAX_VALUES);
    return;
  }
  const RawValue* values = sensor.getValues();
  for (size_t i = 0; i < size; i++) {
    switch (values[i].type) {
      case CValueType::INT:
        LOG_DEBUG("Adding value_type: %d value: %d\n", values[i].key, values[i].value.as_int);
        data.values[data.values_count].which_value = Value_as_int_tag;
        data.values[data.values_count].value.as_int = values[i].value.as_int;
        break;
      case CValueType::FLOAT:
        LOG_DEBUG("Adding value_type: %d value: %.2f\n", values[i].key, values[i].value.as_float);
        data.values[data.values_count].which_value = Value_as_float_tag;
        data.values[data.values_count].value.as_float = values[i].value.as_float;
        break;
      default:
        LOG_ERROR("Unknown value_type: %d\n", values[i].key);
        continue;
    }
    data.values[data.values_count].value_type = values[i].key;
    data.values_count++;
  }
  strcpy(data.sensor_id, sensorCommunityId);
  data.sensor_pin = sensorPin;
}

void LoRaHandler::send() {
  ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  if (!pb_encode(&ostream, &Data_msg, &data)) {
    // error
    LOG_ERROR("Error during pb_encode: %s\n", ostream.errmsg);
  }

  LOG_INFO("Sending %d bytes to gateway\n", ostream.bytes_written);

  // send packet
  LoRa.beginPacket();
  LoRa.write(buffer, ostream.bytes_written);
  if (LoRa.endPacket() == 0) {
    LOG_ERROR("Failed to send packet\n");
  }
  data.values_count = 0;
}

void LoRaHandler::sleep() {
  LoRa.sleep();
}

void LoRaHandler::wakeUp() {
  LoRa.idle();
}
