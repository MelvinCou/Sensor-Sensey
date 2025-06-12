#pragma once
#include "webConfigurer.h"

/**
 * @brief Setup LoRa
 */
void loRaBegin(WebConfigurer& conf);

/**
 * @brief Handle a connection (must be in a for loop)
 */
void receive(String sensorComUrl);
