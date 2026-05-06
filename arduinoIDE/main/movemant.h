#include <math.h>
#include "Arduino.h"
#ifndef MOVEMANT_H
#define MOVEMANT_H

#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepperX(AccelStepper::DRIVER, 8, 9);
AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);

MultiStepper steppers;

int maxSpeed = 1000;
int acceleration = 500;
int defaultSpeed = 750;
extern const int lsy;

bool reletiveCords = true;
int feedrate = 0;

void movemantInit() {
  stepperX.setSpeed(200);
  stepperX.setMaxSpeed(maxSpeed);
  stepperX.setAcceleration(acceleration);
  stepperY.setSpeed(-500);
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);

  steppers.addStepper(stepperX);
  steppers.addStepper(stepperY);
}

void moveToHome() {
  Serial.println("Homing");
  stepperY.setSpeed(-defaultSpeed);

  bool reachedX = true;
  bool reachedY = false;
  bool reachedZ = true;
  while (true) {
    if (!digitalRead(lsy)) reachedY = true;

    if (!reachedY) stepperY.runSpeed();

    if (reachedX && reachedY && reachedZ) break;
  }
  stepperY.setSpeed(200);
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

void moveTo(int xPos, bool moveX, int yPos, bool moveY, int zPos, bool moveZ, int ePos, bool moveE, int F) {
  Serial.println("");
  Serial.println("Moving to: ");
  if (moveX) {
    Serial.print(" X: ");
    Serial.print(xPos);
  }
  if (moveY) {
    Serial.print(" Y: ");
    Serial.print(-yPos);
  }
  if (moveZ) {
    Serial.print(" Z: ");
    Serial.print(zPos);
  }
  if (moveE) {
    Serial.print(" E: ");
    Serial.print(ePos);
  }

  long positions[2];
  if (reletiveCords) {
    if (moveX) positions[0] = xPos + stepperX.currentPosition();
    else positions[0] = stepperX.currentPosition();
    if (moveY) positions[1] = yPos + stepperY.currentPosition();
    else positions[1] = stepperY.currentPosition();
  }

  stepperX.setMaxSpeed(F);
  stepperY.setMaxSpeed(F);
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
}

#endif