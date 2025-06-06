#pragma once

#include "t-beam/boards.h"

namespace sleepHandler {
extern volatile bool activeSensor;
extern volatile bool buttonClicked;

esp_err_t interruptibleSleep(unsigned int sleepSeconds = 10);
void esp32WakeUp();

void IRAM_ATTR buttonHandler();
void handleButtonClick();
}  // namespace sleepHandler
