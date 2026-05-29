#ifndef MOVEMANT_H
#define MOVEMANT_H

#include "HardwareSerial.h"
#include <math.h>
#include "Arduino.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepperX(AccelStepper::DRIVER, 8, 9);
AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);

MultiStepper steppers;

float stmmx = 1750;
float stmmy = -90;

float size = 165;

int maxSpeed = 1000;
int acceleration = 500;
int defaultSpeed = 1000;
extern const int lsx;
extern const int lsy;
extern const bool skipHomeing;

bool reletiveCords = true;
int feedrate = 0;

void movemantInit() {
  stepperX.setSpeed(defaultSpeed);
  stepperX.setMaxSpeed(maxSpeed);
  stepperX.setAcceleration(acceleration);
  stepperY.setSpeed(-defaultSpeed);
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);

  steppers.addStepper(stepperX);
  steppers.addStepper(stepperY);
}

void moveToHome() {
  Serial.println("Homing");
  if (skipHomeing) return;
  stepperX.setSpeed(7500);
  stepperY.setSpeed(defaultSpeed * stmmy);

  bool reachedX = false;
  bool reachedY = false;
  bool reachedZ = true;
  while (true) {
    if (!digitalRead(lsx)) reachedX = true;
    if (!digitalRead(lsy)) reachedY = true;

    if (!reachedX) stepperX.runSpeed();
    if (!reachedY) stepperY.runSpeed();

    if (reachedX && reachedY && reachedZ) break;
  }
  stepperX.setSpeed(-defaultSpeed);
  stepperY.setSpeed(defaultSpeed);
  reachedZ = false;

  delay(50);
  while (true) {
    if (digitalRead(lsx)) reachedX = false;
    if (digitalRead(lsy)) reachedY = false;

    if (reachedX) stepperX.runSpeed();
    if (reachedY) stepperY.runSpeed();

    if (!reachedX && !reachedY && !reachedZ) break;
  }
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  Serial.println("Homing done");
}

void moveTo(float xPos, bool moveX, float yPos, bool moveY, float zPos, bool moveZ, float ePos, bool moveE, float F, bool addDelay = true) {
  Serial.println("");
  Serial.print("Moving to: ");
  if (moveX) {
    Serial.print(" X: ");
    Serial.print(xPos);
  }
  if (moveY) {
    Serial.print(" Y: ");
    Serial.print(yPos);
  }
  if (moveZ) {
    Serial.print(" Z: ");
    Serial.print(zPos);
  }
  if (moveE) {
    Serial.print(" E: ");
    Serial.print(ePos);
  }
  Serial.print(" At feedrate: ");
  Serial.println(F);

  long positions[2];
  if (reletiveCords) {
    if (moveX) positions[0] = xPos * stmmx + stepperX.currentPosition();
    else positions[0] = stepperX.currentPosition();
    if (moveY) positions[1] = yPos * stmmy + stepperY.currentPosition();
    else positions[1] = stepperY.currentPosition();
  }
  else {
    if (moveX) positions[0] = (xPos - size / 2) * stmmx;
    else positions[0] = stepperX.currentPosition();
    if (moveY) positions[1] = (yPos - size / 2) * stmmy;
    else positions[1] = stepperY.currentPosition();
  }

  if (positions[0] > 0 || positions[1] < 0 || F == -1) {
    Serial.println("Movemant set to outside of range, terminating command.");
    return;
  }

  float dx = abs(stepperX.targetPosition() - positions[0]);
  float dy = abs(stepperY.targetPosition() - positions[1]);

  float dist = sqrt(dx * dx + dy * dy);

  float totalSpeed = (F / 60.0) * max(stmmx, stmmy);

  float speedX = totalSpeed * (dx / dist);
  float speedY = totalSpeed * (dy / dist);

  stepperX.setMaxSpeed(speedX);
  stepperY.setMaxSpeed(speedY);
  //if (maxStepSpeed <= 0) return;

  steppers.moveTo(positions);

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    steppers.run();
  }

  //if (addDelay) delay(50);
}

#endif