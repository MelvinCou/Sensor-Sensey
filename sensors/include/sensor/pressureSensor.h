#pragma once

#include <Adafruit_BMP280.h>

#include "sensor.h"

class PressureSensor : public Sensor {
 public:
  PressureSensor();
  void begin();
  void sense() override;
  void setLocalAltitudeOffset(float altitude);

 private:
  Adafruit_BMP280 m_bmp;
  float localAltitudeOffset;
};
