#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"

const int lsx = 2;
const int lsy = 3;

sdCard sdc(53);
// const char* path = "3dbenchy.gx";
const char* path = "strecher.gx";
bool printing = true;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();

  pinMode(lsx, INPUT_PULLUP);
  pinMode(lsy, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);

  printing = true;
  //Serial.println(sdc.readLine(path, 0));

  // delay(1000);
  movemantInit();
  if (false) {
    moveToHome();
    delay(1000);
    moveTo(-10, false, -10, true, 0, false, 0, false, 200);
    if (false) {
      moveTo(-2000, true, -2000, true, 0, false, 0, false, 1000);
      moveTo(-2000, true, -2000, false, 0, false, 0, false, 1000);
      moveTo(-2000, true, -2000, false, 0, false, 0, false, 1000);
      moveTo(-2000, true, -2000, false, 0, false, 0, false, 1000);
      moveTo(-2000, true, -2000, false, 0, false, 0, false, 1000);
    }
  }
  /*delay(200);
  moveTo(1000, true, 2000, true, 0, false, 0, false, 1000);
  delay(200);
  moveTo(1000, true, -1000, true, 0, false, 0, false, 750);
  delay(200);
  moveTo(1000, true, 2000, true, 0, false, 0, false, 1000);*/
  /*moveTo(2000, true, -2000, true, 0, false, 0, false, 1000);

  /*for (int i = 42; i < 46; i++) {
    executeGCline(path, i);
    delay(1000);
  }*/
  //stepperY.setSpeed(100);
  //digitalWrite(10, LOW);

  for (int l = 0; l < 80; l++) {
    //if (!printing) break;
    if (l != 1) executeGCline(path, l);
    delay(100);
  }
  Serial.println("Finished printing");
}

void loop() {
  //Serial.println(digitalRead(lsx));
  //delay(1000);
}