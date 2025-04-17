#include "sensor/pressureSensor.h"

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <t-beam/utilities.h>

#include <Logger.hpp>

#define ID_TEMPERATURE 0
#define ID_PRESSURE 1
#define ID_ALTITUDE 2

PressureSensor::PressureSensor() {
  m_valuesCount = 3;
  m_values = new RawValue[m_valuesCount];

  strcpy(m_values[ID_TEMPERATURE].key, "temperature");
  strcpy(m_values[ID_PRESSURE].key, "pressure");
  strcpy(m_values[ID_ALTITUDE].key, "altitude");
}

void PressureSensor::begin() {
  // Initialize sensor
  bool found = m_bmp.begin(PRESSURE_SENSOR_I2C_ADDRESS);  // Default is I2C address 0x76 when SDO is floating (I2C
  // mode), 0x77 when plugged on ground
  if (!found) {
    found = m_bmp.begin(0x77);
    if (found) LOG_INFO("BMP280 found at 0x77\n");
  } else {
    LOG_INFO("BMP280 found at %x\n", PRESSURE_SENSOR_I2C_ADDRESS);
  }
  if (!found) LOG_ERROR("BMP280 not found!\n");

  // Print chip id
  // Wire.beginTransmission(PRESSURE_SENSOR_I2C_ADDRESS);  // start writing to sensor
  // Wire.write(0xD0);                                     // sends the register address we want to lookup to the sensor
  // Wire.endTransmission();                               // end writing
  // Wire.requestFrom(PRESSURE_SENSOR_I2C_ADDRESS, 1);     // setup read settings (address, number of bytes)
  // uint8_t chipID = Wire.read();                         // read the next byte
  // Serial.printf("Chip ID: 0x%02X\n", chipID);           // 0x58 is BMP (ours), 0x60 is BME (fake)

  // Optional : config
  // m_bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,    // Operating mode
  //                 Adafruit_BMP280::SAMPLING_X2,    // Temperature oversampling
  //                 Adafruit_BMP280::SAMPLING_X16,   // Pressure oversampling
  //                 Adafruit_BMP280::FILTER_X16,     // Filtering
  //                 Adafruit_BMP280::STANDBY_MS_500  // Standby time
  // );
}

void PressureSensor::sense() {
  // Get data
  float temperature = m_bmp.readTemperature();
  float pressure = m_bmp.readPressure() / 100.0F;              // Convert Pa to hPa
  float altitude = m_bmp.readAltitude(LOCAL_ALTITUDE_OFFSET);  // Adjusted to local sea level pressure - Offset is defined in utilities.h

  // Print data
  LOG_INFO("Temperature = %.2f °C\n", temperature);
  LOG_INFO("Pressure = %.2f hPa\n", pressure);
  LOG_INFO("Approx Altitude = %.2f m\n", altitude);

  snprintf(m_values[ID_TEMPERATURE].value, sizeof(m_values[ID_TEMPERATURE].value), "%.2f", temperature);
  snprintf(m_values[ID_PRESSURE].value, sizeof(m_values[ID_PRESSURE].value), "%.2f", pressure);
  snprintf(m_values[ID_ALTITUDE].value, sizeof(m_values[ID_ALTITUDE].value), "%.2f", altitude);
}
