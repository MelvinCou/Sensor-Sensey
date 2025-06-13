#include <webConfigurer.h>

#include <Logger.hpp>

#include "loRaHandler.h"
#include "sensor/dustSensor.h"
#include "sensor/pressureSensor.h"
#include "sleepHandler.h"
#include "t-beam/boards.h"

// Initialize web server configurer
WebConfigurer webConfigurer;

// Initialize sensors
DustSensor dustSensor;
PressureSensor pressureSensor;

void setup() {
  // Reset configuration to erase sensitive data on SPIFFS
  // webConfigurer.reset();

  // Configure web server before setting boards up as there we initiate Lora within
  webConfigurer.configure();

  LOG_INFO("Setting up boards...\n");
  setupBoards(webConfigurer);

  webConfigurer.serverListen();

  // Initialize Pressure sensors
  pressureSensor.setLocalAltitudeOffset(webConfigurer.getLocalAltOffset());
  pressureSensor.begin();

  // Configures pin input with internal pull-up
  pinMode(LAUNCH_SENSOR_PIN, INPUT_PULLUP);

  // Attach interrupt on falling edge (press button)
  attachInterrupt(digitalPinToInterrupt(LAUNCH_SENSOR_PIN), sleepHandler::buttonHandler, FALLING);

  // Configures pin input with internal pull-up
  pinMode(LAUNCH_SENSOR_PIN, INPUT_PULLUP);

  // Attach interrupt on falling edge (press button)
  attachInterrupt(digitalPinToInterrupt(LAUNCH_SENSOR_PIN), sleepHandler::buttonHandler, FALLING);

  // When power is turned on, a delay is required.
  delay(1500);
}

void loop() {
  if (sleepHandler::buttonClicked) {
    sleepHandler::buttonClicked = false;
    sleepHandler::handleButtonClick();
  }

  if (sleepHandler::activeSensor) {
    LOG_INFO("Sensors ON - Collect data...\n");

    // Only trigger dust sense if active
    if (webConfigurer.isDustSensorActive()) {
      dustSensor.sense();
      LoRaHandler::addValueToSend(dustSensor, webConfigurer.getSensorId(), webConfigurer.getDustSensorPin());
    }

    // Only trigger pressure sense if active
    if (webConfigurer.isPressureSensorActive()) {
      pressureSensor.sense();
      LoRaHandler::addValueToSend(pressureSensor, webConfigurer.getSensorId(), webConfigurer.getPressureSensorPin());
    }

    LoRaHandler::send();

    sleepHandler::interruptibleSleep();
  } else {
    // Have webServer actif
    webConfigurer.handleClient();

    delay(100);
  }
}
