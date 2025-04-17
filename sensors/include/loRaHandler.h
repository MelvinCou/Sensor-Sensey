#pragma once

#include "sensor/sensor.h"

namespace LoRaHandler
{
    void loRaBegin();

    void addValueToSend(const Sensor& sensor);

    void send();
} // namespace LoRaHandler
