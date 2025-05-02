#include "Arduino.h"
#include "loRaHandler.h"
#include "wiFiHandler.h"

void setup() {
  Serial.begin(115200);
  sleep(1);
  wiFiConnection();
  loRaBegin();
}

void loop() { receive(); }