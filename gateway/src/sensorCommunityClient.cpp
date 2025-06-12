#include "sensorCommunityClient.h"

#include <webConfigurer.h>

#include <Logger.hpp>

#include "ArduinoJson.h"
#include "HTTPClient.h"

HTTPClient http;
unsigned char json[128];

// HTTP request to sensor.community
void requestSensorCommunity(WebConfigurer& conf, String xSensor, String xPin) {
  if (WiFi.status() == WL_CONNECTED) {
    // HTTP request construction with headers
    http.begin(conf.getSensorCommunityUrl());
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", xSensor);
    http.addHeader("X-Pin", xPin);

    // JSON construction
    JsonDocument doc;
    JsonArray sensordatavalues = doc["sensordatavalues"].to<JsonArray>();
    // Add object on array
    JsonObject value0 = sensordatavalues.add<JsonObject>();
    value0["value_type"] = "temperature";
    value0["value"] = "10";

    // Serialize JSON data before POST request
    size_t payloadSize = serializeJson(doc, json);

    LOG_INFO("Sending HTTP POST request of size %d to sensor API...\n", payloadSize);
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