#pragma once

#include "t-beam/boards.h"

namespace sleepHandler {
esp_err_t esp32Sleep();

void esp32WakeUp();
}  // namespace sleepHandler
