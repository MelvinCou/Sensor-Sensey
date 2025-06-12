#include "loRaHandler.h"

#include <RadioLib.h>
#include <data.pb.h>
#include <pb_decode.h>
#include <ValueTypeStr.h>

#include <Logger.hpp>

#define RADIO_BOARD_AUTO
#include <RadioBoards.h>
#include <webConfigurer.h>
#include <sensorCommunityClient.h>
Radio radio = new RadioModule();

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

void printReception(const Data& data);

void loRaBegin(WebConfigurer& conf) {
  // initialize SX1262 with default settings
  Serial.print(F("[SX1262] Initializing ... "));
  int state =
      radio.begin(conf.getLoraRadioFreq(), conf.getLoraRadioBw(), conf.getLoraRadioSf(), conf.getLoraRadioCr(), conf.getLoraRadioSw());
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
}

uint8_t buffer[Data_size + 1];
Data decoded = Data_init_zero;
pb_istream_t istream;

void receive(String sensorComUrl) {
  // check if the flag is set
  if (receivedFlag) {
    // reset flag
    receivedFlag = false;

    size_t packetSize = radio.getPacketLength();
    int state = radio.readData(buffer, sizeof(buffer));

    if (state == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      LOG_DEBUG("[SX1262] Received packet!\n");

      // decode data
      istream = pb_istream_from_buffer(buffer, packetSize);
      if (!pb_decode(&istream, &Data_msg, &decoded)) {
        LOG_ERROR("Error during pb_decode: %s\n", istream.errmsg);
        return;
      }
      printReception(decoded);

      // Send API request
      requestSensorCommunity(sensorComUrl, decoded);
    } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      LOG_ERROR("CRC error!");

    } else {
      // some other error occurred
      LOG_ERROR("failed, code %d", state);
    }
  }
}

void printReception(const Data& data) {
#if LOG_LEVEL >= LOG_LEVEL_INFO
  LOG_INFO("[SX1262] Data: sensor_id: %s, sensor_pin: %d\n", decoded.sensor_id, decoded.sensor_pin);
  for (size_t i = 0; i < data.values_count; i++) {
    const char* valueType = ValueTypeStr::_from_index(decoded.values[i].value_type)._to_string();
    switch (data.values[i].which_value) {
      case Value_as_int_tag:
        LOG_INFO("[SX1262]\t %d value_type: %s, value: %d\n", i, valueType, decoded.values[i].value.as_int);
        break;
      case Value_as_float_tag:
        LOG_INFO("[SX1262]\t %d value_type: %s, value: %.2f\n", i, valueType, decoded.values[i].value.as_float);
        break;
      default:
        LOG_ERROR("[SX1262]\t %d Unknown value_type: %s\n", i, valueType);
        break;
    }
  }
#endif
#if LOG_LEVEL >= LOG_LEVEL_DEBUG
  // print RSSI (Received Signal Strength Indicator)
  LOG_DEBUG("[SX1262] RSSI:\t\t %.2f dBm\n", radio.getRSSI());
  // print SNR (Signal-to-Noise Ratio)
  LOG_DEBUG("[SX1262] SNR:\t\t %.2f dB\n", radio.getSNR());
  // print frequency error
  LOG_DEBUG("[SX1262] Frequency error:\t %.2f Hz\n", radio.getFrequencyError());
#endif
}
