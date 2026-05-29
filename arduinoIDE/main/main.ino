#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"
#include "joystick.h"

const int lsx = 2;
const int lsy = 3;
const int enx = 12;
const int eny = 7;

const bool skipHomeing = false;

sdCard sdc(53);
joystick joystick(13, A2, A3);
//gcr gcreader();
const char* path = "TC.gx";
bool printing = true;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();
  joystick.begin();

  pinMode(lsx, INPUT_PULLUP);
  pinMode(lsy, INPUT_PULLUP);
  pinMode(enx, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(eny, OUTPUT);
  digitalWrite(enx, LOW);
  digitalWrite(eny, LOW);

  movemantInit();

  //moveTo(-10, true, -10, true, 0, false, 0, false, 1000);
  /*float maxLine = 120;
  for (int l = 0; l < maxLine; l++) {
    if (l != 1) executeGCline(path, l); //the second line in gcode files is a preview image
    Serial.print(l / maxLine * 100);
    Serial.print("%");
    delay(10);
  }
  moveToHome();
  Serial.println("Finished printing");*/
}

void loop() {
  Serial.print(joystick.getDirX());
  Serial.print(joystick.getDirY());
  Serial.println(joystick.pressed());
  //Serial.println(digitalRead(13));
  delay(500);
}