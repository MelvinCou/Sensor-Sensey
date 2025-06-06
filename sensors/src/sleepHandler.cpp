#include "sleepHandler.h"

#include <Logger.hpp>

#include "loRaHandler.h"

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define CLICK_DEBOUNCE_DELAY 300   // Avoid double clicks if the interval between two clicks is less than 300 ms.

unsigned long lastClickTime = 0;

namespace sleepHandler {
volatile bool activeSensor = false;
volatile bool buttonClicked = false;

esp_err_t interruptibleSleep(unsigned int sleepSeconds) {
  // First we configure the wake up source.
  esp_sleep_enable_timer_wakeup(sleepSeconds * uS_TO_S_FACTOR);  // Timer

  // Sleep some process
  LoRaHandler::sleep();

  // Launch light sleep
  Serial.println("Going to sleep now");
  esp_err_t result = esp_light_sleep_start();

  return result;
}

void esp32WakeUp() {
  // WakeUp sleeping process
  LoRaHandler::wakeUp();
}

// Interruption handler - called on each clic on LAUNCH_SENSOR_PIN
// Places function in RAM (IRAM) for execution at any time
void IRAM_ATTR buttonHandler() {
  unsigned long currentTime = millis();
  if (currentTime - lastClickTime > CLICK_DEBOUNCE_DELAY) {
    buttonClicked = true;
    lastClickTime = currentTime;
  }
}

// Modify the value of the activeSensor
void handleButtonClick() {
  activeSensor = !activeSensor;
  Serial.print("🔘 Detected CLIC ! Sensors : ");
  Serial.println(activeSensor ? "ON" : "OFF");
}
}  // namespace sleepHandler
