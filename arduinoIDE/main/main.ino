#include "printer.h"
#include "hotend.h"

printer printer;
hotend hotend(10, A0);

void setup() {
  Serial.begin(9600);
  // printer.begin();
  // printer.selectFunction();

  hotend.waitForTemp(100);
}

void loop() {
  // hotend.updatePID(80);
  // Serial.println(hotend.getTemp());
  delay(100);
}