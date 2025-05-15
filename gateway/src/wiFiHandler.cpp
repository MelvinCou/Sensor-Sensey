#include "wiFiHandler.h"

#include <Logger.hpp>

#include "WiFi.h"

#define ssid "YOUR_SSID"
#define password "YOUR_PASSWORD"

// Event manager: Connected to access point
void connectedToWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  LOG_INFO("\nConnected to the WiFi network");
}

// Event manager : IP address obtained
void gotIpFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  LOG_INFO("Local ESP32 IP: %s", WiFi.localIP().toString().c_str());
}

// Event manager : WiFi disconnection
void disconnectedFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  LOG_INFO("\nDisconnected from WiFi. Attempting to reconnect...");
  WiFi.begin(ssid, password);  // Try to connect again
}

void wiFiConnection() {
  LOG_INFO("Initializing WiFi...");

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
  LOG_INFO("\nConnecting to WiFi...");
}
