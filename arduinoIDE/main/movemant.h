#include <math.h>
#include "Arduino.h"
#ifndef MOVEMANT_H
#define MOVEMANT_H

#include <AccelStepper.h>

AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);

int maxSpeed = 1000;
int acceleration = 500;
int defaultSpeed = 1000;
extern const int lsy;

bool reletiveCords = true;
int feedrate = 0;

void movemantInit() {
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);
}

void moveToHome() {
  Serial.println("Homing");
  stepperY.setSpeed(defaultSpeed);

  bool reachedX = true;
  bool reachedY = false;
  bool reachedZ = true;
  while (true) {
    if (!digitalRead(lsy)) reachedY = true;

    if (!reachedY) stepperY.runSpeed();

    if (reachedX && reachedY && reachedZ) break;
  }
  stepperY.setSpeed(-200);
  reachedX = false;
  reachedZ = false;

  delay(50);
  while (true) {
    if (digitalRead(lsy)) reachedY = false;

    if (reachedY) stepperY.runSpeed();

    if (!reachedX && !reachedY && !reachedZ) break;
  }
  stepperY.setCurrentPosition(0);
  Serial.println("Homing done");
}

void moveTo(int xPos, int yPos, int zPos, int ePos, int F) {
  int deltaY;

  if (reletiveCords) {
    deltaY = yPos;

    stepperY.moveTo(stepperY.currentPosition() + yPos);
  }
  else {
    deltaY = yPos - stepperY.currentPosition();

    stepperY.moveTo(yPos);
  }
  
  float d = sqrt(sq(deltaY));
  float t = d / F;

  stepperY.setMaxSpeed(deltaY / t);

  while (true) {
    stepperY.run();

    if (stepperY.distanceToGo() == 0) break;
  }
}

#endif