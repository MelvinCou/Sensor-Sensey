#include "dustSensor.h"

#include "data.pb.h"
#include <HardwareSerial.h>
#include <Logger.hpp>
#include <t-beam/utilities.h>

Data readDustSensorData() {
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

  // Create and return the message to transfert via loRa protocole
  Data message = Data_init_zero;

  message.sensor_pin = DUST_SENSOR_COM_PIN;
  strcpy(message.sensor_id, SENSOR_COM_ID);
  message.values_count = 1;
  strcpy(message.values[0].value_type, DUST_SENSOR_COM_TYPE);
  snprintf(message.values[0].value, sizeof(message.values[0].value), "%.2f", voltage);
  return message;
}

void setUpDustSensor() {
    pinMode(DUST_ILED_PIN, OUTPUT);
    delay(280);
    LOG_INFO("Dust Sensor set up !\n");
}