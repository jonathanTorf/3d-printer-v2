#include "Arduino.h"
#include "joystick.h"

joystick::joystick(int s, int x, int y) {
  sw = s;
  vrx = x;
  vry = y;
}

joystick::begin() {
  pinMode(sw, INPUT);
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
}

int joystick::getDirX() {
  if (analogRead(vrx) - base >= th) return 1 * xMult;
  else if (analogRead(vrx) - base <= -th) return -1 * xMult;
  else return 0;
}

int joystick::getDirY() {
  if (analogRead(vry) - base >= th) return 1 * yMult;
  else if (analogRead(vry) - base <= -th) return -1 * yMult;
  else return 0;
}

bool joystick::pressed() {
  if (digitalRead(sw) == 1) return false;
  else return true;
}