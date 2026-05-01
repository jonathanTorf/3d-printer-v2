#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"

const int lsy = 2;

sdCard sdc(53);
const char* path = "3dbenchy.gx";
bool printing = false;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();
  pinMode(lsy, INPUT_PULLUP);

  printing = true;
  //Serial.println(sdc.readLine(path, 0));
  for (int i = 30; i < 46; i++) {
    //executeGCline(path, i);
    // delay(200);
  }

  delay(1000);
  movemantInit();
  moveToHome();
}

void loop() {
/*  int STEP_PIN = 11;
for (int i = 0; i < 200; i++) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(1500);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(1500);
}
delay(1000);
  digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));*/
}
