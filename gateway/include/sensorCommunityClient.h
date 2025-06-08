#pragma once

#include "Arduino.h"
#include "webConfigurer.h"


/**
 * @brief Function used for request sensor community through http
 */
void requestSensorCommunity(WebConfigurer& conf, String xSensor, String xPin);
