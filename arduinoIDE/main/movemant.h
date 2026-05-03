#include <math.h>
#include "Arduino.h"
#ifndef MOVEMANT_H
#define MOVEMANT_H//c

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

void moveTo(int xPos, bool moveX, int yPos, bool moveY, int zPos, bool moveZ, int ePos, bool moveE, int F) {
  Serial.println("");
  Serial.println("Moving to: ");
  if (moveX) {
    Serial.println("X: ");
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
  int deltaX, deltaY, deltaZ, deltaE;

  if (reletiveCords) {
    deltaX = xPos;
    deltaY = yPos;
    deltaZ = zPos;
    // deltaE = ePos;

    stepperY.moveTo(stepperY.currentPosition() + yPos);
  }
  else {
    //deltaX = xPos - stepperX.currentPosition();
    deltaY = yPos - stepperY.currentPosition();
    //deltaZ = zPos - stepperZ.currentPosition();
    //deltaE = ePos - stepperE.currentPosition();

    stepperY.moveTo(yPos);
  }
  
  float d = sqrt(sq(deltaX) + sq(deltaY) + sq(deltaZ) + sq(deltaE));
  float t = d / F;

  stepperY.setMaxSpeed(deltaY / t);

  if (stepperY.targetPosition() >= 0) {
    Serial.println("Movemant index out of range");
    return;
  }

  bool reachedY = !moveY;
  while (!reachedY) {
    if (moveY) stepperY.run();

    if (stepperY.distanceToGo() == 0) reachedY = true;
  }
}

#endif