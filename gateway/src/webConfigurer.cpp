#include "webConfigurer.h"

#include <ESPmDNS.h>
#include <WebConfig.h>
#include <WebServer.h>

#include <Logger.hpp>

// Web server params
#define PARAM_WIFI_SSID "wifiSsid"
#define PARAM_WIFI_PASSWORD "wifiPassword"
#define PARAM_SENSOR_COM_PROTOCOLE "sensorComProtocole"
#define PARAM_SENSOR_COM_DOMAIN "sensorComDomain"
#define PARAM_SENSOR_COM_ENDPOINT "sensorComEndpoint"
#define PARAM_LORA_RADIO_FREQ "loraRadioFreq"
#define PARAM_LORA_RADIO_BW "loraRadioBw"
#define PARAM_LORA_RADIO_SF "loraRadioSf"
#define PARAM_LORA_RADIO_CR "loraRadioCr"
#define PARAM_LORA_RADIO_SW "loraRadioSw"

// clang-format off

String params = "["
  "{"
    "'name':'" + String(PARAM_WIFI_SSID) + "',"
    "'label':'Wifi SSID',"
    "'type':"+String(INPUTTEXT)+","
    "'default':''"
  "},"
  "{"
    "'name':'" + String(PARAM_WIFI_PASSWORD) + "',"
    "'label':'Wifi Password',"
    "'type':"+String(INPUTTEXT)+","
    "'default':''"
  "},"
  "{"
    "'name':'" + String(PARAM_SENSOR_COM_PROTOCOLE) + "',"
    "'label':'Sensor Community URL Protocole',"
    "'type':"+String(INPUTSELECT)+","
    "'options':["
      "{'v':'http','l':'http'},"
      "{'v':'https','l':'https'}],"
    "'default':'https'"
  "},"
  "{"
    "'name':'" + String(PARAM_SENSOR_COM_DOMAIN) + "',"
    "'label':'Sensor Community URL Domain',"
    "'type':"+String(INPUTTEXT)+","
    "'default':'api.sensor.community'"
  "},"
  "{"
    "'name':'" + String(PARAM_SENSOR_COM_ENDPOINT) + "',"
    "'label':'Sensor Community URL Endpoint',"
    "'type':"+String(INPUTTEXT)+","
    "'default':'/v1/push-sensor-data/'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_FREQ) + "',"
    "'label':'Lora Radio Frequency',"
    "'type':"+String(INPUTFLOAT)+","
    "'default':'868.0'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_BW) + "',"
    "'label':'Lora Radio Bandwidth',"
    "'type':"+String(INPUTFLOAT)+","
    "'default':'125.0'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_SF) + "',"
    "'label':'Lora Radio Spreading Factor',"
    "'type':"+String(INPUTNUMBER)+","
    "'default':'7'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_CR) + "',"
    "'label':'Lora Radio Coding Rate',"
    "'type':"+String(INPUTNUMBER)+","
    "'default':'7'"
  "},"
  "{"
    "'name':'" + String(PARAM_LORA_RADIO_SW) + "',"
    "'label':'Lora Radio Sync Word',"
    "'type':"+String(INPUTNUMBER)+","
    "'min':0,'max':1000,"
    "'default':'171'"
  "}"
  "]";

// clang-format on

void WebConfigurer::configure() {
  LOG_INFO("\nConfiguring");

  // Set description
  conf.setDescription(params);
  LOG_INFO("\nDescription set");

  // Set config
  conf.readConfig();
  LOG_INFO("\nConfig Read");
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

String WebConfigurer::getWifiSsid() {
  return conf.getString(PARAM_WIFI_SSID);
}

String WebConfigurer::getWifiPassword() {
  return conf.getString(PARAM_WIFI_PASSWORD);
}

String WebConfigurer::getSensorCommunityUrl() {
  char buffer[100];
  snprintf(buffer, sizeof(buffer), "%s://%s%s", conf.getString(PARAM_SENSOR_COM_PROTOCOLE).c_str(),
           conf.getString(PARAM_SENSOR_COM_DOMAIN).c_str(), conf.getString(PARAM_SENSOR_COM_ENDPOINT).c_str());
  return String(buffer);
}

float WebConfigurer::getLoraRadioFreq() {
  return conf.getFloat(PARAM_LORA_RADIO_FREQ);
}

float WebConfigurer::getLoraRadioBw() {
  return conf.getFloat(PARAM_LORA_RADIO_BW);
}

uint8_t WebConfigurer::getLoraRadioSf() {
  return conf.getInt(PARAM_LORA_RADIO_SF);
}

uint8_t WebConfigurer::getLoraRadioCr() {
  return conf.getInt(PARAM_LORA_RADIO_CR);
}

uint8_t WebConfigurer::getLoraRadioSw() {
  return conf.getInt(PARAM_LORA_RADIO_SW);
}