#include "loRaHandler.h"
#include <Logger.hpp>
#include <LoRa.h>
#include <Logger.hpp>
#include <message.pb.h>
#include <pb_decode.h>

#define CONFIG_RADIO_FREQ 868E6
#define CONFIG_RADIO_BW 125.0

#define SPI_SCK 9
#define SPI_MOSI 10
#define SPI_MISO 11
#define SPI_SS 8

#define LORA_RESET 12
#define LORA_DIO0 24

void onReceive(int packetSize);

void loRaBegin() {
  //SPI.begin(5, 19, 27);
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MISO, SPI_SS); // SCK, MISO, MOSI, SS
  LoRa.setPins(SPI_SS, LORA_RESET, LORA_DIO0);//SS, RST_LoRa, DIO0

  if (!LoRa.begin(CONFIG_RADIO_FREQ)) {
    Serial.println("Starting LoRa failed!");
  }
  /*
  LoRa.setSignalBandwidth(CONFIG_RADIO_BW * 1000);
  LoRa.setSpreadingFactor(7);
  LoRa.setPreambleLength(16);
  LoRa.setSyncWord(0xAB);
  LoRa.disableCrc();
  LoRa.disableInvertIQ();
  LoRa.setCodingRate4(7);
  */

  // register the receive callback
  LoRa.onReceive(onReceive);
  LoRa.receive();
}

uint8_t buffer[Message_size * 2];
Message decoded = Message_init_zero;
pb_istream_t istream;

void onReceive(int packetSize) {
  // received a packet
  LOG_INFO("Received packet from sensors \n");

  LoRa.readBytes(buffer, packetSize);
  istream = pb_istream_from_buffer(buffer, packetSize);
  if (!pb_decode(&istream, &Message_msg, &decoded)) {
    LOG_ERROR("Error during pb_decode: %s\n", istream.errmsg);
    return;
  }

  LOG_INFO("Output: str: %s ; kind: %d\n", decoded.str, decoded.kind);
}
