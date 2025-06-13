#pragma once

#include <data.pb.h>

#include "Arduino.h"

/**
 * @brief Function used for request sensor community through http
 */
void requestSensorCommunity(String& sensorComUrl, const Data& data);
