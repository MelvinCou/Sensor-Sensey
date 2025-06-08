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

  /// @brief Gets Sensor Community Identifier
  /// @return is the sensor community identifier char*
  const char* getSensorId();

  /// @brief Is Dust Sensor Active
  /// @return a bool wether dust sensor is active
  bool isDustSensorActive();

  /// @brief Gets Dust Sensor Pin on Sensor Community
  /// @return it the dust sensor pin as an int
  int getDustSensorPin();

  /// @brief Is Pressure Sensor Active
  /// @return a bool wether pressure sensor is active
  bool isPressureSensorActive();

  /// @brief Gets Pressure Sensor Pin on Sensor Community
  /// @return it the pressure sensor pin as an int
  int getPressureSensorPin();

  /// @brief Gets Local Altitude Offset
  /// @return the local altitude offset as a float
  float getLocalAltOffset();

  /// @brief Gets Lora frequency
  /// @return the frequency as a long
  long getLoraRadioFreq();

  /// @brief Gets Lora BandWidth
  /// @return the bandwidth as a float
  float getLoraRadioBw();

 private:
  /// @brief Is the WebServer instance
  WebServer server;

  /// @brief Is the Webconfig configuration
  WebConfig conf;
};