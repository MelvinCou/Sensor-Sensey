#pragma once

#include "sensor.h"

class DustSensor : public Sensor
{
public:
    DustSensor();
    void sense() override;
};
