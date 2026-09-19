#include "printer.h"
#include "hotend.h"

printer printer;
hotend hotend(9, A0);

void setup() {
  Serial.begin(9600);
  // printer.begin();
  // printer.selectFunction();
}

void loop() {
  hotend.updatePID(80);
  delay(300);
}