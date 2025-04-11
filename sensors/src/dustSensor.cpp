#include "dustSensor.h"

#include <message.pb.h>
#include <HardwareSerial.h>
#include <Logger.hpp>

// Allocating the dust sensor's pins on ESP 32 board
const int AOUT_PIN = 2;
const int ILED_PIN = 13;
// IMPORTANT: This implementation of the dust sensor is based on 5v

Message readDustSensorData() {
  // Setup sensor data reading
  // TODO: Maybe only do this part once ?
  pinMode(ILED_PIN, OUTPUT);
  delay(280);
  LOG_INFO("Dust Sensor set up  !");

  // Activate ILED
  digitalWrite(ILED_PIN, HIGH);
  delayMicroseconds(280); 

  // Convert analogue value to voltage
  int analogValue = analogRead(AOUT_PIN);  
  float voltage = analogValue * (5 / 4095.0); 

  // Deactivate ILED
  delayMicroseconds(280);
  digitalWrite(ILED_PIN, LOW);
  delayMicroseconds(280);

  // Print value
  LOG_INFO("Raw Value: %d | Voltage: %.2f", analogValue, voltage);

  // Create and return the message to transfert via loRa protocole
  Message message = Message_init_zero;
  message.kind = SensorKind::SensorKind_DustSensor;
  snprintf(message.str, sizeof(message.str), "%.2f", voltage);
  return message;
}
