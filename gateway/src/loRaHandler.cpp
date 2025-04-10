#include "loRaHandler.h"

#include <RadioLib.h>
#include <message.pb.h>
#include <pb_decode.h>

#include <Logger.hpp>

#define RADIO_BOARD_AUTO
#include <RadioBoards.h>
Radio radio = new RadioModule();

#define CONFIG_RADIO_FREQ 868.0F
// Bandwidth
#define CONFIG_RADIO_BW 125.0F
// spreading factor
#define CONFIG_RADIO_SF 7U
#define CONFIG_RADIO_CR 7U
// sync word
#define CONFIG_RADIO_SW 0xAB

// save transmission states between loops
int transmissionState = RADIOLIB_ERR_NONE;

// flag to indicate that a packet was received
volatile bool receivedFlag = false;

// this function is called when a complete packet
// is transmitted or received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  // we sent or received a packet, set the flag
  receivedFlag = true;
}

void loRaBegin() {
  // initialize SX1262 with default settings
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin(CONFIG_RADIO_FREQ, CONFIG_RADIO_BW, CONFIG_RADIO_SF, CONFIG_RADIO_CR, CONFIG_RADIO_SW);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) {
      delay(10);
    }
  }

  // set the function that will be called
  // when new packet is received
  radio.setPacketReceivedAction(setFlag);

#if defined(INITIATING_NODE)
  // send the first packet on this node
  Serial.print(F("[SX1262] Sending first packet ... "));
  transmissionState = radio.startTransmit("Hello World!");
  transmitFlag = true;
#else
  // start listening for LoRa packets on this node
  Serial.print(F("[SX1262] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) {
      delay(10);
    }
  }
#endif
}

uint8_t buffer[Message_size * 2];
Message decoded = Message_init_zero;
pb_istream_t istream;

void onReceive() {
  // check if the flag is set
  if (receivedFlag) {
    // reset flag
    receivedFlag = false;

    size_t packetSize = radio.getPacketLength();
    int state = radio.readData(buffer, sizeof(buffer));

    if (state == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      LOG_DEBUG("[SX1262] Received packet!\n");

      // print data of the packet
      istream = pb_istream_from_buffer(buffer, packetSize);
      if (!pb_decode(&istream, &Message_msg, &decoded)) {
        LOG_ERROR("Error during pb_decode: %s\n", istream.errmsg);
        return;
      }
      LOG_INFO("[SX1262] Data: str: %s ; kind: %d\n", decoded.str, decoded.kind);
      // print RSSI (Received Signal Strength Indicator)
      LOG_DEBUG("[SX1262] RSSI:\t\t %.2f dBm\n", radio.getRSSI());
      // print SNR (Signal-to-Noise Ratio)
      LOG_DEBUG("[SX1262] SNR:\t\t %.2f dB\n", radio.getSNR());
      // print frequency error
      LOG_DEBUG("[SX1262] Frequency error:\t %.2f Hz\n", radio.getFrequencyError());

    } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      LOG_ERROR("CRC error!");

    } else {
      // some other error occurred
      LOG_ERROR("failed, code %d", state);
    }
  }
}
