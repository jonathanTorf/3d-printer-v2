#include "printer.h"
#include "hotend.h"

printer printer;
hotend hotend(10, A0);

void setup() {
  Serial.begin(9600);
  // printer.begin();
  // printer.selectFunction();
  // analogWrite(10, 204);
  // hotend.updatePID(80);
  // delay(300);
  // hotend.updatePID(80);
}

void loop() {
  hotend.updatePID(80);
  // Serial.println(hotend.getTemp());
  delay(100);
}