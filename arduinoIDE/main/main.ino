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

  delay(1000);
  movemantInit();
  moveToHome();
  moveTo(2000, true, -2000, true, 0, false, 0, false, 1000);
  moveTo(2000, true, -2000, true, 0, false, 0, false, 1000);

  for (int i = 42; i < 46; i++) {
    executeGCline(path, i);
    delay(1000);
  }
}

void loop() {

}
