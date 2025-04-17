#pragma once

#include "sensor.h"
#include <Adafruit_BMP280.h>

class PressureSensor : public Sensor
{
public:
    PressureSensor();
    void sense() override;
private:
    Adafruit_BMP280 m_bmp;
};
