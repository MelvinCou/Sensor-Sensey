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

  // When the power is turned on, a delay is required.
  delay(1500);
}

void loop() {
  dustSensor.sense();
  LoRaHandler::addValueToSend(dustSensor);
  pressureSensor.sense();
  LoRaHandler::addValueToSend(pressureSensor);

  LoRaHandler::send();

  // esp_err_t result = sleepHandler::esp32Sleep();

  // Check if sleep has worked
  // if (result == ESP_OK) {
  //   Serial.println("Woke up from light sleep");
  //   sleepHandler::esp32WakeUp();
  // } else {
  //   Serial.printf("Sleep failed! Error: %d\n", result);
  // }

  delay(15000);
}
