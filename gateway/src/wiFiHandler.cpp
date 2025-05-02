#include "wiFiHandler.h"

#include "ArduinoJson.h"
#include "HTTPClient.h"
#include "data.pb.h"

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* sensorCommunityUrl = "http://api.sensor.community/v1/push-sensor-data/";

// HTTP request to sensor.community
void requestSensorCommunity(String xSensor, String xPin) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // HTTP request construction with headers
    http.begin(sensorCommunityUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", xSensor);
    http.addHeader("X-Pin", xPin);

    // JSON construction
    JsonDocument doc;
    JsonArray sensordatavalues = doc["sensordatavalues"].to<JsonArray>();
    // Add object on array
    JsonObject value0 = sensordatavalues.createNestedObject();
    value0["value_type"] = "temperature";
    value0["value"] = "10";

    // Serialize JSON data before POST request
    String json;
    serializeJson(doc, json);

    Serial.println("Sending HTTP POST request to sensor API...");
    int httpCode = http.POST(json);
    Serial.printf("HTTP CODE, code: %d\n", httpCode);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.printf("HTTP POST returned code: %d\n", httpCode);
      Serial.println("HTTP Response:");
    } else {
      Serial.printf("HTTP POST failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi not connected, cannot send HTTP request");
  }
}

void wiFiConnection() {
  Serial.println("Initializing WiFi...");

  // Reset WiFi module to avoid errors
  WiFi.disconnect(true);  // Clean previous state
  WiFi.mode(WIFI_OFF);
  delay(100);

  // Configure station mode (say to WiFi that is used only for connection and not router)
  WiFi.mode(WIFI_STA);

  // Register event handlers
  WiFi.onEvent(connectedToWiFi, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(gotIpFromWiFi, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(disconnectedFromWiFi, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  // Launch connection
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi...");
}

// Event manager: Connected to access point
void connectedToWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) { Serial.println("\nConnected to the WiFi network"); }

// Event manager : IP address obtained
void gotIpFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  requestSensorCommunity("esp32-1234", "7");
}

// Event manager : WiFi disconnection
void disconnectedFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  Serial.println("\nDisconnected from WiFi. Attempting to reconnect...");
  WiFi.begin(ssid, password);  // Try to connect again
}