#include "loRaHandler.h"
#include "message.pb.h"
#include "t-beam/boards.h"

int counter = 0;

void setup() {
  setupBoards();
  // When the power is turned on, a delay is required.
  delay(1500);
}

Message original = Message_init_zero;

void loop() {
  original.kind = SensorKind::SensorKind_BMP280;
  strcpy(original.str, "coucou sdfsfsdf_");

  sendMessage(original);
  delay(5000);
}
