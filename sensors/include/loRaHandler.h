#pragma once

#include <webConfigurer.h>

#include "sensor/sensor.h"

namespace LoRaHandler {
void loRaBegin(WebConfigurer& conf);

void addValueToSend(const Sensor& sensor, const char* sensorCommunityId, uint32_t sensorPin);

void send();

void sleep();

void wakeUp();
}  // namespace LoRaHandler
