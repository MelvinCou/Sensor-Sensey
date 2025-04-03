#include <LoRa.h>

#define CONFIG_RADIO_FREQ 868E6
#define CONFIG_RADIO_BW 125.0

uint8_t buffer[100];

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    buffer[i] = static_cast<uint8_t>(LoRa.read());
    Serial.print(buffer[i]);
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);

  SPI.begin(9, 11, 10);
  LoRa.setPins(18,14,26);
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
  //LoRa.onReceive(onReceive);
  //LoRa.receive();
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  } else {
    //Serial.println("No packet");
  }
}
