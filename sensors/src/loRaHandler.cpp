#include "loRaHandler.h"

#include <LoRa.h>
#include <pb_encode.h>

#include <Logger.hpp>

#include "data.pb.h"
#include "t-beam/utilities.h"

void LoRaHandler::loRaBegin() {
  LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
  if (!LoRa.begin(CONFIG_RADIO_FREQ)) {
    LOG_ERROR("Starting LoRa failed!\n");
  }
  LoRa.setSignalBandwidth(CONFIG_RADIO_BW * 1000);
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
#define MAX_VALUES 3

void LoRaHandler::addValueToSend(const Sensor& sensor) {
  const size_t& size = sensor.getValuesCount();
  if (size + data.values_count > MAX_VALUES) {
    LOG_ERROR("Overflow of values : %d (size) + %d (values_count) > %d (MAX_VALUES)\n", size, data.values_count, MAX_VALUES);
    return;
  }
  const RawValue* values = sensor.getValues();
  for (size_t i = 0; i < size; i++) {
    LOG_DEBUG("Adding value_type: %s value: %s\n", values[i].key, values[i].value);

    strcpy(data.values[data.values_count].value_type, values[i].key);
    strcpy(data.values[data.values_count].value, values[i].value);
    data.values_count++;
  }
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
