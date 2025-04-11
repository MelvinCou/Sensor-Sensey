#include "loRaHandler.h"

#include <LoRa.h>
#include <pb_encode.h>

#include <Logger.hpp>

#include "t-beam/utilities.h"

void loRaBegin() {
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

uint8_t buffer[Data_size];
pb_ostream_t ostream;

void sendMessage(const Data& message) {
  ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  if (!pb_encode(&ostream, &Data_msg, &message)) {
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
}
