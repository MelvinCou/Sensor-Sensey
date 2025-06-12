#include "sleepHandler.h"

#include <Logger.hpp>

#include "loRaHandler.h"

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define CLICK_DEBOUNCE_DELAY 300   // Avoid double clicks if the interval between two clicks is less than 300 ms.

unsigned long lastClickTime = 0;

namespace sleepHandler {
volatile bool activeSensor = false;
volatile bool buttonClicked = false;

void interruptibleSleep(unsigned int sleepSeconds) {
  // Wait until the button is released before configuring the sleep mode.
  while (gpio_get_level(GPIO_NUM_38) == 0) {
    LOG_INFO("Waiting for button release...\n");
    delay(10);
  }

  // Wait a little longer for the debounce
  delay(100);

  // First we configure the wake up source.
  esp_sleep_enable_timer_wakeup(sleepSeconds * uS_TO_S_FACTOR);

  // Sleep some process
  LoRaHandler::sleep();

  // Launch light sleep
  LOG_INFO("Going to sleep now\n");
  esp_err_t result = esp_light_sleep_start();

  // Check if sleep has worked and launch back sleep process
  if (result == ESP_OK) {
    LOG_INFO("Woke up from light sleep\n");
    sleepHandler::esp32WakeUp();
  } else {
    LOG_ERROR("Sleep failed! Error: %d\n", result);
  }
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
  LOG_INFO("🔘 Detected CLIC ! Sensors : %s\n", activeSensor ? "ON" : "OFF");
}
}  // namespace sleepHandler
