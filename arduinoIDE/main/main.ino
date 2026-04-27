#include "sd.h"
#include "gcodeRead.h"

sdCard sdc(53);
const char* path = "3dbenchy.gx";
bool printing = false;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();

  printing = true;
  //Serial.println(sdc.readLine(path, 0));
  for (int i = 30; i < 46; i++) {
    //executeGCline(path, i);
    // delay(200);
  }
  // executeGCline(path, 61);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(10, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 200; i++) {
    digitalWrite(11, HIGH);
    delayMicroseconds(500);   // pulse width
    digitalWrite(11, LOW);
    delayMicroseconds(500);   // speed control
  }

  delay(1000);

  // Reverse direction
  digitalWrite(10, !digitalRead(10));
}
