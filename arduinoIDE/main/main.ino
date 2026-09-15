#include "printer.h"

printer printer;

void setup() {
  printer.begin();
  printer.selectFunction();
}

void loop() {}