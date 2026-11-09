#include "printer.h"
#include "hotend.h"

printer printer;
hotend hotend(13, A4);

void setup() {
  Serial.begin(9600);
  printer.begin();
  // printer.selectFunction();

  // hotend.waitForTemp(45);
}

void loop() {
  // hotend.updatePID(80);
  //Serial.println(hotend.getTemp());
  delay(1000);
}