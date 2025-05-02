#include "sensor/dustSensor.h"

#include <HardwareSerial.h>
#include <t-beam/utilities.h>

#include <Logger.hpp>

#define ID_ANALOG_VOLTAGE 0
#define ID_VOLTAGE 1

DustSensor::DustSensor() {
  m_valuesCount = 2;
  m_values = new RawValue[m_valuesCount];

  m_values[ID_ANALOG_VOLTAGE].key = ValueType::analogValue;
  m_values[ID_ANALOG_VOLTAGE].type = CValueType::INT;

  m_values[ID_VOLTAGE].key = ValueType::voltage;
  m_values[ID_VOLTAGE].type = CValueType::FLOAT;

  pinMode(DUST_ILED_PIN, OUTPUT);
}

void DustSensor::sense() {
  // Activate ILED
  digitalWrite(DUST_ILED_PIN, HIGH);
  delayMicroseconds(280);
  // Convert analogue value to voltage
  int analogValue = analogRead(DUST_AOUT_PIN);
  float voltage = analogValue * (VCC_3V / 4095.0);

  // Deactivate ILED
  digitalWrite(DUST_ILED_PIN, LOW);

  // Print value
  LOG_INFO("Raw Value: %d | Voltage: %.2f\n", analogValue, voltage);

  m_values[ID_ANALOG_VOLTAGE].value.as_int = analogValue;
  m_values[ID_VOLTAGE].value.as_float = voltage;
}
