#include "printer.h"
#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"
#include "joystick.h"
#include "UI.h"
#include <Wire.h>

sdCard sdc(53);
joystick joystick(13, A2, A3);
UI ui;

printer::printer() {}

printer::begin() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();
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

printer::selectFunction() {
  int func = 0;
  while (joystick.getDirX() != 1) delay(100);
  
  while (!joystick.pressed()) {
    if (joystick.getDirX() != 0) {
      func += joystick.getDirX();
      if (func < 0) func = 0;
      if (func > funcAmt) func = funcAmt;
      ui.printFunction(func);

      Serial.print("Function: ");
      Serial.println(func);
    }
    while (joystick.getDirX() != 0) delay(100);

    delay(100);
  }
  Serial.println("Joystick pressed");
  switch (func) {
    case 0:
      selectPath();
      break;
  }
}

printer::selectPath() {
  int maxFiles = 20;
  path = "/";
  char outFiles[maxFiles][32];

  File dir = SD.open(path);

  if (!dir) {
    Serial.println("Failed to open directory");
    return;
  }

  int count = 0;

  while (true) {
    File entry = dir.openNextFile();

    if (!entry) break;

    if (entry.isDirectory()) {
      entry.close();
      continue;
    }

    String name = entry.name();
    name.toLowerCase();

    if (name.endsWith(".gx")) {
      if (count < maxFiles) {
        strncpy(outFiles[count], name.c_str(), 31);
        outFiles[count][31] = '\0';

        Serial.print("GX File Found: ");
        Serial.println(outFiles[count]);

        count++;
      }
    }
    entry.close();
  }
  dir.close();

  Serial.print("Total GX files: ");
  Serial.println(count);

  //while (joystick.pressed()) delay(100);
  int fileNum = 0;
  lcd.setCursor(0, 1);
  lcd.print(outFiles[0]);
  Serial.println(outFiles[0]);
  while (!joystick.pressed()) {
    if (joystick.getDirY() != 0) {
      fileNum += joystick.getDirY();
      if (fileNum < 0) fileNum = 0;
      else if (fileNum > count - 1) fileNum = count - 1;
      lcd.setCursor(0, 1);
      lcd.print(outFiles[fileNum]);
      while (joystick.getDirY() != 0) delay(100);
    }

    delay(100);
  }
  path = outFiles[fileNum];

  Serial.print("Path selected: ");
  Serial.println(path);
}

printer::print(const char* path) {

}