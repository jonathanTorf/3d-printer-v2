#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"

const int lsx = 2;
const int lsy = 3;

sdCard sdc(53);
const char* path = "3dbenchy.gx";
//const char* path = "strecher.gx";
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

  movemantInit();

  for (int l = 0; l < 150; l++) {
    //if (!printing) break;
    if (l != 1) executeGCline(path, l);
    delay(50);
  }
  moveToHome();
  //moveTo(-10 + size / 2, true, -10 + size / 2, true, 0, false, 0, false, 1000);
  Serial.println("Finished printing");
}

void loop() {

}