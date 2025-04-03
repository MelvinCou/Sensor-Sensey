// Only supports SX1276/SX1278
#include <LoRa.h>

#include "t-beam/boards.h"

#define CONFIG_RADIO_FREQ 868E6
//#define CONFIG_RADIO_OUTPUT_POWER 17
#define CONFIG_RADIO_BW 125.0

int counter = 0;

void setup() {
  setupBoards();
  // When the power is turned on, a delay is required.
  delay(1500);

  Serial.println("LoRa Sender");
  LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
  if (!LoRa.begin(CONFIG_RADIO_FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  /*
  LoRa.setTxPower(CONFIG_RADIO_OUTPUT_POWER);
  LoRa.setSignalBandwidth(CONFIG_RADIO_BW * 1000);
  LoRa.setSpreadingFactor(7);
  LoRa.setPreambleLength(16);
  LoRa.setSyncWord(0xAB);
  LoRa.disableCrc();
  LoRa.disableInvertIQ();
  LoRa.setCodingRate4(7);
  */
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  //LoRa.print("hello ");
  LoRa.print(counter);
  if(LoRa.endPacket() == 0) {
    Serial.println("Failed to send packet");
  }

  counter++;
  delay(5000);
}
