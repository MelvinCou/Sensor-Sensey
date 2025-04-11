#include "dustSensor.h"

#include <message.pb.h>
#include <HardwareSerial.h>
#include <Logger.hpp>
#include <t-beam/utilities.h>

Message readDustSensorData() {
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
  Message message = Message_init_zero;
  message.kind = SensorKind::SensorKind_DustSensor;
  snprintf(message.str, sizeof(message.str), "%.2f", voltage);
  return message;
}

void setUpDustSensor() {
    pinMode(DUST_ILED_PIN, OUTPUT);
    delay(280);
    LOG_INFO("Dust Sensor set up !\n");
}