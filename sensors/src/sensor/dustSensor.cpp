#include "sensor/dustSensor.h"

#include <HardwareSerial.h>
#include <t-beam/utilities.h>

#include <Logger.hpp>

#define ID_ANALOG_VOLTAGE 0
#define ID_VOLTAGE 1

DustSensor::DustSensor() {
  m_valuesCount = 2;
  m_values = new RawValue[m_valuesCount];

  strcpy(m_values[ID_ANALOG_VOLTAGE].key, "analogValue");
  strcpy(m_values[ID_VOLTAGE].key, "voltage");

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

  snprintf(m_values[ID_ANALOG_VOLTAGE].value, sizeof(m_values[ID_ANALOG_VOLTAGE].value), "%d", analogValue);
  snprintf(m_values[ID_VOLTAGE].value, sizeof(m_values[ID_VOLTAGE].value), "%.2f", voltage);
}
