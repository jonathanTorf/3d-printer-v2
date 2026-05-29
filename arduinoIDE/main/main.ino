#include "sd.h"
#include "gcodeRead.h"
#include "movemant.h"
#include "joystick.h"
#include "UI.h"
#include "printer.h"

printer printer;

void setup() {
  printer.begin();

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

void loop() {}