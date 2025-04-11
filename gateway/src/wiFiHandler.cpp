#include "wiFiHandler.h"
#include "HTTPClient.h"

const char* ssid = "your_WiFi_SSID";
const char* password = "your_WiFi_password";

void wiFiConnection() {
    Serial.println("Initializing WiFi...");
    
    // Reset WiFi module to avoid errors
    WiFi.disconnect(true); // Clean previous state
    WiFi.mode(WIFI_OFF);
    delay(100);
  
    // Configure station mode (say to WiFi that is used only for connection and not router)
    WiFi.mode(WIFI_STA);
  
    // Register event handlers
    WiFi.onEvent(connectedToAp, ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(disconnectedFromAp, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  
    // Launch connection
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting to WiFi...");
}

// Event manager: Connected to access point
void connectedToAp(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
    Serial.println("\nConnected to the WiFi network");
}
  
// Event manager : WiFi disconnection
void disconnectedFromAp(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo) {
    Serial.println("\nDisconnected from WiFi. Attempting to reconnect...");
    WiFi.begin(ssid, password); // Try to connect again
}