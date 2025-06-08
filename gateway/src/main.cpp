#include "Arduino.h"
#include "loRaHandler.h"
#include "wiFiHandler.h"
#include "webConfigurer.h"

WebConfigurer webConfigurer;

void setup() {
  // Reset configuration to erase sensitive data on SPIFFS 
  // webConfigurer.reset();

  Serial.begin(115200);
  sleep(1);

  // Setup wifi
  // Configure webConfigurer before initialising wifi connections
  webConfigurer.configure();
  wiFiConnection(webConfigurer);
  webConfigurer.serverListen();

  loRaBegin(webConfigurer);
}

void loop() {
  webConfigurer.handleClient();
  receive();
}