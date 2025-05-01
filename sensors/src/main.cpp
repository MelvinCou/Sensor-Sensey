#include <Logger.hpp>

#include "loRaHandler.h"
#include "sensor/dustSensor.h"
#include "sensor/pressureSensor.h"
#include "t-beam/boards.h"

DustSensor dustSensor;
PressureSensor pressureSensor;

void setup() {
  LOG_INFO("Setting up boards...\n");
  setupBoards();
  pressureSensor.begin();

  // When the power is turned on, a delay is required.
  delay(1500);
}

void loop() {
  dustSensor.sense();
  LoRaHandler::addValueToSend(dustSensor);
  pressureSensor.sense();
  LoRaHandler::addValueToSend(pressureSensor);

  LoRaHandler::send();
  delay(5000);
}
