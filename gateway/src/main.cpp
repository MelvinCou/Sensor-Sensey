#include "Arduino.h"
#include "loRaHandler.h"

void setup() {
  Serial.begin(115200);
  sleep(1);
  loRaBegin();
}

void loop() { onReceive(); }