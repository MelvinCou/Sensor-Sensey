#include "sensorCommunityClient.h"

#include <data.pb.h>
#include <Logger.hpp>
#include <ValueTypeStr.h>

#include "ArduinoJson.h"
#include "HTTPClient.h"

unsigned char json[256];

JsonDocument createJsonDocument(const Data& data) {
  JsonDocument doc;
  JsonArray sensordatavalues = doc["sensordatavalues"].to<JsonArray>();

  // Add values received to JsonArray
  for (size_t i = 0; i < data.values_count; i++) {

    const char* valueType = ValueTypeStr::_from_index(data.values[i].value_type)._to_string();

    JsonObject jsonObj;

    // Add JsonObject if value is correct
    switch (data.values[i].which_value) {
      case Value_as_int_tag:
        jsonObj = sensordatavalues.add<JsonObject>();
        jsonObj["value_type"] = valueType;
        jsonObj["value"] = std::to_string(data.values[i].value.as_int).c_str();
        break;
      case Value_as_float_tag:
        jsonObj = sensordatavalues.add<JsonObject>();
        jsonObj["value_type"] = valueType;
        jsonObj["value"] = std::to_string(data.values[i].value.as_float).c_str();
        break;
      default:
        LOG_ERROR("[SX1262]\t %d Unknown value_type: %s\n", i, valueType);
        break;
    }
  }

  return doc;
}

// HTTP request to sensor.community
void requestSensorCommunity(String& sensorComUrl, const Data& data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // HTTP request construction with headers
    http.begin(sensorComUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", data.sensor_id);
    http.addHeader("X-Pin", String(data.sensor_pin));

    // Serialize JSON data before POST request
    size_t payloadSize = serializeJson(createJsonDocument(data), json);

    LOG_INFO("Sending HTTP POST request of size %d to sensor API...\n", payloadSize);
    LOG_TRACE("SENSOR URL: %s\n", sensorComUrl.c_str());
    
    LOG_TRACE("Sending raw data: \n %s\n", json);

    int httpCode = http.POST(json, payloadSize);
    LOG_INFO("HTTP CODE, code: %d\n", httpCode);

    if (httpCode > 0) {
      String payload = http.getString();
      LOG_INFO("HTTP POST returned code: %d\n", httpCode);
    } else {
      LOG_ERROR("HTTP POST failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    LOG_ERROR("WiFi not connected, cannot send HTTP request");
  }
}