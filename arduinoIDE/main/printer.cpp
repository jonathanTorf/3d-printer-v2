#include "printer.h"
#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"
#include "joystick.h"
#include "UI.h"

printer::printer() {}

printer::begin() {
  sdCard sdc(53);
  joystick joystick(13, A2, A3);
  UI ui;

  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();
  sdc.listGXFiles();
  joystick.begin();
  ui.begin();

  pinMode(lsx, INPUT_PULLUP);
  pinMode(lsy, INPUT_PULLUP);
  pinMode(enx, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(eny, OUTPUT);
  digitalWrite(enx, LOW);
  digitalWrite(eny, LOW);

  movemantInit();
}