#include "data.pb.h"
#include "loRaHandler.h"
#include "t-beam/boards.h"
#include "dustSensor.h"

int counter = 0;

void setup() {
  setupBoards();
  // When the power is turned on, a delay is required.
  delay(1500);
}

Data original = Data_init_zero;

void loop() {
  original.sensor_pin = 7;
  strcpy(original.sensor_id, "esp32-1234");
  original.values_count = 1;
  strcpy(original.values[0].value_type, "temperature");
  strcpy(original.values[0].value, "30");

  sendMessage(original);
  delay(5000);
}
