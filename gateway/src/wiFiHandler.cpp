#include "wiFiHandler.h"

#include <ESPmDNS.h>
#include <webConfigurer.h>

#include <Logger.hpp>

#include "WiFi.h"

#define AP_SSID "gatewaySsid"
#define WEB_SERVER_MDNS "gateway"  // When connected on AP_SSID wifi, access the web server through gateway.local !

// Event manager: Connected to access point
void connectedToWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  LOG_INFO("\nConnected to the WiFi network");
}

// Event manager : IP address obtained
void gotIpFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
  LOG_INFO("Local ESP32 IP: %s", WiFi.localIP().toString().c_str());
}

void wiFiConnection(WebConfigurer& conf) {
  LOG_INFO("Initializing WiFi...");

  // Reset WiFi module to avoid errors
  WiFi.disconnect(true);  // Clean previous state
  WiFi.mode(WIFI_OFF);
  delay(100);

  // Allow both STA and AP wifi connection (Ap to create local wifi and create a WebConfigurer and STA to connect to another wifi)
  WiFi.mode(WIFI_AP_STA);

  // Register event handlers
  WiFi.onEvent(connectedToWiFi, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(gotIpFromWiFi, ARDUINO_EVENT_WIFI_STA_GOT_IP);

  // Manage wifi reconnection directly to use WebConfigurer
  WiFi.onEvent(
      [&conf](WiFiEvent_t event, WiFiEventInfo_t info) {
        LOG_INFO("Disconnected from WiFi. Attempting to reconnect...");
        WiFi.begin(conf.getWifiSsid(), conf.getWifiPassword());
      },
      ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  // Start STA connection
  WiFi.begin(conf.getWifiSsid(), conf.getWifiPassword());
  LOG_INFO("\nConnecting to WiFi...");

  // Start AP wifi
  WiFi.softAP(AP_SSID);
  if (MDNS.begin(WEB_SERVER_MDNS)) {
    LOG_INFO("\nMDNS responder started");
  }
}
