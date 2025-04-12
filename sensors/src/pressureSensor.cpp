#include "pressureSensor.h"

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <t-beam/utilities.h>

#include <Logger.hpp>

#include "data.pb.h"

Adafruit_BMP280 bmp;
// TODO : currently theses var ar global, so names must be different across sensors but there may be cleaner approaches
Data pressureMessage = Data_init_zero;

void setupPressureSensor() {
  // Initialize sensor
  bool found = bmp.begin(0x76);  // Default is I2C address 0x76 when SDO is floating (I2C mode), 0x77 when plugged on ground
  if (!found) {
    found = bmp.begin(0x77);
    if (found) LOG_INFO("BMP280 found at 0x77\n");
  } else {
    LOG_INFO("BMP280 found at 0x76\n");
  }
  if (!found) LOG_ERROR("BMP280 not found!\n");

  // Print chip id
  Wire.beginTransmission(0x76);
  Wire.write(0xD0);
  Wire.endTransmission();
  Wire.requestFrom(0x76, 1);
  uint8_t chipID = Wire.read();
  Serial.printf("Chip ID: 0x%02X\n", chipID);  // 0x58 is BMP (ours), 0x60 is BME (fake)

  // Optional : config
  // bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,    // Operating mode
  //                 Adafruit_BMP280::SAMPLING_X2,    // Temperature oversampling
  //                 Adafruit_BMP280::SAMPLING_X16,   // Pressure oversampling
  //                 Adafruit_BMP280::FILTER_X16,     // Filtering
  //                 Adafruit_BMP280::STANDBY_MS_500  // Standby time
  // );
}

Data readPressureSensorData() {
  // Get data
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;  // Convert Pa to hPa
  float altitude = bmp.readAltitude(1017);       // Adjusted to local sea level pressure

  // Print data
  LOG_INFO("Temperature = %.2f °C\n", temperature);
  LOG_INFO("Pressure = %.2f hPa\n", pressure);
  LOG_INFO("Approx Altitude = %.2f m\n", altitude);

  // Wait
  delay(2000);

  // Create and return message
  pressureMessage.sensor_pin = PRESSURE_SENSOR_COM_PIN;
  strcpy(pressureMessage.sensor_id, SENSOR_COM_ID);
  pressureMessage.values_count = 1;
  strcpy(pressureMessage.values[0].value_type, PRESSURE_SENSOR_COM_TYPE);
  snprintf(pressureMessage.values[0].value, sizeof(pressureMessage.values[0].value), "%.2f", temperature);
  return pressureMessage;
}
