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
    executeGCline(path, i);
    // delay(200);
  }
  // executeGCline(path, 61);
}

void loop() {
  // put your main code here, to run repeatedly:

}
