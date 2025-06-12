#include <Logger.hpp>

#include "loRaHandler.h"
#include "sensor/dustSensor.h"
#include "sensor/pressureSensor.h"
#include "sleepHandler.h"
#include "t-beam/boards.h"

DustSensor dustSensor;
PressureSensor pressureSensor;

void setup() {
  LOG_INFO("Setting up boards...\n");
  setupBoards();
  pressureSensor.begin();

  // Configures pin input with internal pull-up
  pinMode(LAUNCH_SENSOR_PIN, INPUT_PULLUP);

  // Attach interrupt on falling edge (press button)
  attachInterrupt(digitalPinToInterrupt(LAUNCH_SENSOR_PIN), sleepHandler::buttonHandler, FALLING);

  // When the power is turned on, a delay is required.
  delay(1500);
}

void loop() {
  if (sleepHandler::buttonClicked) {
    sleepHandler::buttonClicked = false;
    sleepHandler::handleButtonClick();
  }

  if (sleepHandler::activeSensor) {
    LOG_INFO("Sensors ON - Collect data...\n");

    dustSensor.sense();
    LoRaHandler::addValueToSend(dustSensor);
    pressureSensor.sense();
    LoRaHandler::addValueToSend(pressureSensor);

    LoRaHandler::send();

    sleepHandler::interruptibleSleep();
  } else {
    LOG_INFO("Sensors OFF - Wait...\n");

    delay(3000);
  }
}
