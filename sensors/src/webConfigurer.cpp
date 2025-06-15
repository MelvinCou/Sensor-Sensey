#include "webConfigurer.h"

#include <ESPmDNS.h>
#include <WebConfig.h>
#include <WebServer.h>

#include <Logger.hpp>

#define AP_SSID "sensorSsid"
#define WEB_SERVER_MDNS "sensors"  // When connected on AP_SSID wifi, access the web server through sensors.local !

// Web server params
#define PARAM_SENSOR_ID "sensorId"
#define PARAM_DUST_SENSOR_ACTIVE "dustSensorActive"
#define PARAM_DUST_SENSOR_PIN "dustSensorPin"
#define PARAM_PRESSURE_SENSOR_ACTIVE "pressureSensorActive"
#define PARAM_PRESSURE_SENSOR_PIN "pressureSensorPin"
#define PARAM_LOCAL_ALT_OFFSET "localAltitudeOffset"
#define PARAM_LORA_RADIO_FREQ "loraRadioFreq"
#define PARAM_LORA_RADIO_BW "loraRadioBw"

// clang-format off

String params = "["
  "{"
    "'name':'" + String(PARAM_SENSOR_ID) + "',"
    "'label':'Sensor Community Identifier',"
    "'type':"+String(INPUTTEXT)+","
    "'default':'esp32-1234'"
  "},"
  "{"
    "'name':'" + String(PARAM_DUST_SENSOR_ACTIVE) + "',"
    "'label':'Dust Sensor Active',"
    "'type':"+String(INPUTCHECKBOX)+","
    "'default':'1'"
  "},"
  "{"
    "'name':'" + String(PARAM_DUST_SENSOR_PIN) + "',"
    "'label':'Dust sensor PIN on Sensor Community',"
    "'type':"+String(INPUTNUMBER)+","
    "'default':'7'"
  "},"
  "{"
    "'name':'" + String(PARAM_PRESSURE_SENSOR_ACTIVE) + "',"
    "'label':'Pressure Sensor Active',"
    "'type':"+String(INPUTCHECKBOX)+","
    "'default':'1'"
  "},"
  "{"
    "'name':'" + String(PARAM_PRESSURE_SENSOR_PIN) + "',"
    "'label':'Pressure sensor PIN on Sensor Community',"
    "'type':"+String(INPUTNUMBER)+","
    "'default':'10'"
  "},"
  "{"
    "'name':'" + String(PARAM_LOCAL_ALT_OFFSET) + "',"
    "'label':'Local Altitude Offset in meters',"
    "'type':"+String(INPUTFLOAT)+","
    "'min':0,'max':10000,"
    "'default':'1017.0'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_FREQ) + "',"
    "'label':'Lora Radio Frequency in MHz',"
    "'type':"+String(INPUTNUMBER)+","
    "'min':0,'max':1000,"
    "'default':'868'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_BW) + "',"
    "'label':'Lora Radio Bandwidth',"
    "'type':"+String(INPUTFLOAT)+","
    "'default':'125.0'"
  "}"
  "]";

// clang-format on

/// @brief Inits AP wifi
void initWiFi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID);

  if (MDNS.begin(WEB_SERVER_MDNS)) {
    LOG_INFO("MDNS responder started\n");
  }
}

void WebConfigurer::configure() {
  LOG_INFO("Configuring\n");

  // Set description
  conf.setDescription(params);
  LOG_INFO("Description set\n");

  // Set config
  conf.readConfig();
  LOG_INFO("Config Read\n");

  initWiFi();
}

void WebConfigurer::serverListen() {
  server.on("/", [this] { conf.handleFormRequest(&server); });
  server.begin(80);
}

void WebConfigurer::reset() {
  conf.setDescription("[]");
  conf.writeConfig();
}

void WebConfigurer::serverClose() {
  server.close();
}

void WebConfigurer::handleClient() {
  server.handleClient();
}

// GETTERS

const char* WebConfigurer::getSensorId() {
  return conf.getValue(PARAM_SENSOR_ID);
}

bool WebConfigurer::isDustSensorActive() {
  return conf.getBool(PARAM_DUST_SENSOR_ACTIVE);
}

int WebConfigurer::getDustSensorPin() {
  return conf.getInt(PARAM_DUST_SENSOR_PIN);
}

bool WebConfigurer::isPressureSensorActive() {
  return conf.getBool(PARAM_PRESSURE_SENSOR_ACTIVE);
}

int WebConfigurer::getPressureSensorPin() {
  return conf.getInt(PARAM_PRESSURE_SENSOR_PIN);
}

float WebConfigurer::getLocalAltOffset() {
  return conf.getFloat(PARAM_LOCAL_ALT_OFFSET);
}

long WebConfigurer::getLoraRadioFreq() {
  return conf.getInt(PARAM_LORA_RADIO_FREQ) * 1000000L;
}

float WebConfigurer::getLoraRadioBw() {
  return conf.getFloat(PARAM_LORA_RADIO_BW);
}