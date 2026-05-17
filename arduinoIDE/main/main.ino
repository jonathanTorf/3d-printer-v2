#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"

const int lsx = 2;
const int lsy = 3;
const int enx = 12;
const int eny = 7;

sdCard sdc(53);
//const char* path = "3dbenchy.gx";
const char* path = "TC.gx";
//const char* path = "strecher.gx";
bool printing = true;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();

  pinMode(lsx, INPUT_PULLUP);
  pinMode(lsy, INPUT_PULLUP);
  pinMode(enx, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(eny, OUTPUT);
  digitalWrite(enx, LOW);
  digitalWrite(eny, LOW);

  movemantInit();

  float maxLine = 180;
  for (int l = 0; l < maxLine; l++) {
    //if (!printing) break;
    if (l != 1) executeGCline(path, l); //the second line in gcode files is a preview image
    Serial.print(l / maxLine * 100);
    Serial.print("%");
    delay(25);
  }
  moveToHome();
  Serial.println("Finished printing");
}

void loop() {}