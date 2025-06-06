#include <Logger.hpp>

#include "loRaHandler.h"
#include "sensor/dustSensor.h"
#include "sensor/pressureSensor.h"
#include "sleepHandler.h"
#include "t-beam/boards.h"

DustSensor dustSensor;
PressureSensor pressureSensor;

#define LAUNCH_SENSOR_PIN 38

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
    Serial.println("Sensors ON - Collect data...");

    dustSensor.sense();
    LoRaHandler::addValueToSend(dustSensor);
    pressureSensor.sense();
    LoRaHandler::addValueToSend(pressureSensor);

    LoRaHandler::send();

    esp_err_t result = sleepHandler::interruptibleSleep();

    // Check if sleep has worked and launch back sleep process
    if (result == ESP_OK) {
      Serial.println("Woke up from light sleep");
      sleepHandler::esp32WakeUp();
    } else {
      Serial.printf("Sleep failed! Error: %d\n", result);
    }
  } else {
    Serial.println("Sensors OFF - Wait...");

    delay(2000);
  }
}
