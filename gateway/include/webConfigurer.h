#pragma once

#include <WebConfig.h>

/// @brief Creates a web server and configures the data to display (on the web server), to save and to fetch (on SPIFFS).
class WebConfigurer {
 public:
  WebConfigurer() = default;

  /// @brief Configures WebConfig with defined parameters
  void configure();

  /// @brief Resets all WebConfig parameters
  void reset();

  /// @brief Listen on port 80
  void serverListen();

  /// @brief Close the web server
  void serverClose();

  /// @brief Handle client connection (must be in a for loop)
  void handleClient();

  // GETTERS for each configuration parameter
  
  /// @brief Gets Wifi Ssid to initiate connection
  /// @return the wifi Ssid string
  String getWifiSsid();

  /// @brief Gets Wifi Password to authenticate wifi connection
  /// @return the wifi password string
  String getWifiPassword();

  /// @brief Gets Sensor Community API Url endpoint
  /// @return the sensor community url string
  String getSensorCommunityUrl();

  /// @brief Gets Lora frequency
  /// @return the frequency as a float
  float getLoraRadioFreq();

  /// @brief Gets Lora BandWidth
  /// @return the bandwidth as a float
  float getLoraRadioBw();

  /// @brief Gets Lora Spreading Factor
  /// @return the spreading factor as an uint8_t
  uint8_t getLoraRadioSf();

  /// @brief Gets Lora Coding Rate
  /// @return the coding rate as an uint8_t
  uint8_t getLoraRadioCr();

  /// @brief Gets Lora Sync Word
  /// @return the sync word as an uint8_t
  uint8_t getLoraRadioSw();

 private:
  /// @brief Is the WebServer instance
  WebServer server;

  /// @brief Is the Webconfig configuration
  WebConfig conf;
};