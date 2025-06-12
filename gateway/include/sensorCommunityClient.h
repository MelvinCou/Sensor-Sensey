#pragma once

#include "Arduino.h"
#include <data.pb.h>

/**
 * @brief Function used for request sensor community through http
 */
void requestSensorCommunity(String& sensorComUrl, const Data& data);
