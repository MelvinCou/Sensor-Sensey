#include "sensor/dustSensor.h"

#include <HardwareSerial.h>
#include <t-beam/utilities.h>

#include <Logger.hpp>

#define ID_VO_RAW 0
#define ID_VOLTAGE 1
#define ID_DUST_DENSITY 2

DustSensor::DustSensor() {
  m_valuesCount = 3;
  m_values = new RawValue[m_valuesCount];

  m_values[ID_VO_RAW].key = ValueType::vo_raw;
  m_values[ID_VO_RAW].type = CValueType::INT;

  m_values[ID_VOLTAGE].key = ValueType::voltage;
  m_values[ID_VOLTAGE].type = CValueType::FLOAT;

  m_values[ID_DUST_DENSITY].key = ValueType::dust_density;
  m_values[ID_DUST_DENSITY].type = CValueType::FLOAT;

  pinMode(DUST_ILED_PIN, OUTPUT);
}

void DustSensor::sense() {
  // Activate ILED
  digitalWrite(DUST_ILED_PIN, HIGH);
  delayMicroseconds(280);

  // Read analog value
  int analogValue = analogRead(DUST_AOUT_PIN);
  delayMicroseconds(4);
  
  // Deactivate ILED
  digitalWrite(DUST_ILED_PIN, LOW);
  
  // Get voltage and dust density
  float voltage = (VCC_3300mV / 4096.0) * analogValue * 11; // In mV
  float dust_density; // In mg/m3

  if (voltage >= NO_DUST_VOLTAGE)
  {
    voltage -= NO_DUST_VOLTAGE;
    dust_density = voltage * COV_RATIO / 1000;
  }
  else
    dust_density = 0;

  // Print value
  LOG_INFO("Raw Value: %d | Voltage: %.2f | Dust density: %4.2fmg/m3\n", analogValue, voltage, dust_density);

  m_values[ID_VO_RAW].value.as_int = analogValue;
  m_values[ID_VOLTAGE].value.as_float = voltage;
  m_values[ID_DUST_DENSITY].value.as_float = dust_density;
}
