#include "Arduino.h"
#ifndef MOVEMANT_H
#define MOVEMANT_H

#include <AccelStepper.h>

AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);

int maxSpeed = 1000;
int acceleration = 500;
int defaultSpeed = 500;
extern const int lsy;

void movemantInit() {
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);
}

void moveToHome() {
  stepperY.setSpeed(defaultSpeed);

  bool reachedX = false;
  bool reachedY = false;
  bool reachedZ = false;
  while (true) {
    if (digitalRead(lsy)) reachedY = true;

    if (!reachedY) stepperY.runSpeed();

    if (reachedX && reachedY && reachedZ) break;
  }
}

#endif