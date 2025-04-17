#include <Logger.hpp>

#include "loRaHandler.h"
#include "sensor/dustSensor.h"
#include "sensor/pressureSensor.h"
#include "t-beam/boards.h"

DustSensor dust;
PressureSensor pressure;

void setup() {
  LOG_INFO("Setting up boards...\n");
  setupBoards();
  pressure.begin();

  // When the power is turned on, a delay is required.
  delay(1500);
}

void loop() {
  dust.sense();
  LoRaHandler::addValueToSend(dust);
  pressure.sense();
  LoRaHandler::addValueToSend(pressure);

  LoRaHandler::send();
  delay(5000);
}
