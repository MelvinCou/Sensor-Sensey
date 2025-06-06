#include "sleepHandler.h"

#include <Logger.hpp>

#include "loRaHandler.h"

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 10           // Time ESP32 will go to sleep (in seconds)

esp_err_t sleepHandler::esp32Sleep() {
  // First we configure the wake up source.
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  // Sleep some process
  LoRaHandler::sleep();

  // Launch light sleep
  Serial.println("Going to sleep now");
  esp_err_t result = esp_light_sleep_start();

  return result;
}

void sleepHandler::esp32WakeUp() {
  // WakeUp sleeping process
  LoRaHandler::wakeUp();
}
