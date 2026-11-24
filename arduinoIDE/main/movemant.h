#ifndef MOVEMANT_H
#define MOVEMANT_H

#include "HardwareSerial.h"
#include <math.h>
#include "Arduino.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepperX(AccelStepper::DRIVER, 23, 22);
AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);
AccelStepper stepperZ(AccelStepper::DRIVER, 23, 22);

MultiStepper steppers;

float stmmx = -1750;
float stmmy = -90;
float stmmz = 1;

float size = 165;

#include "printer.h"

int maxSpeed = 1000;
int acceleration = 500;
int defaultSpeed = 500;
extern const int lsx;
extern const int lsy;
extern const int lsz;
extern const bool skipHoming;

bool reletiveCords = true;
int feedrate = 0;

void movemantInit() {
  digitalWrite(ms1, HIGH);
  digitalWrite(ms2, LOW);
  digitalWrite(ms3, LOW);

  stepperX.setSpeed(defaultSpeed);
  stepperX.setMaxSpeed(maxSpeed);
  stepperX.setAcceleration(acceleration);

  stepperY.setSpeed(-defaultSpeed);
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);

  stepperZ.setSpeed(-defaultSpeed / 2);
  stepperZ.setMaxSpeed(maxSpeed / 2);
  stepperZ.setAcceleration(acceleration / 2);

  steppers.addStepper(stepperX);
  steppers.addStepper(stepperY);
  steppers.addStepper(stepperZ);
}

void moveToHome(String axis = "XYZ") {
  bool homeX = axis.indexOf("X") != -1;
  bool homeY = axis.indexOf("Y") != -1;
  bool homeZ = axis.indexOf("Z") != -1;

  Serial.print("Homing");
  if (homeX) Serial.print(" X");
  if (homeY) Serial.print(" Y");
  if (homeZ) Serial.print(" Z");
  Serial.println("...");
  if (skipHoming) return;
  stepperX.setSpeed(defaultSpeed * stmmx);
  stepperY.setSpeed(defaultSpeed * stmmy);
  stepperZ.setSpeed(defaultSpeed * stmmz);

  bool reachedX = !homeX;
  bool reachedY = !homeY;
  bool reachedZ = !homeZ;
  Serial.println("Movieng to ls");
  while (true) {
    if (!digitalRead(lsx)) reachedX = true;
    if (!digitalRead(lsy)) reachedY = true;
    if (!digitalRead(lsz)) reachedZ = true;

    if (!reachedX) stepperX.runSpeed();
    if (!reachedY) stepperY.runSpeed();
    if (!reachedZ) stepperZ.runSpeed();

    if (reachedX && reachedY && reachedZ) break;
  }
  stepperX.setSpeed(defaultSpeed);
  stepperY.setSpeed(defaultSpeed);
  stepperZ.setSpeed(-defaultSpeed);
  reachedX = homeX;
  reachedY = homeY;
  reachedZ = homeZ;

  delay(50);
  Serial.println("Movieng from ls");
  while (true) {
    if (digitalRead(lsx)) reachedX = false;
    if (digitalRead(lsy)) reachedY = false;
    if (digitalRead(lsz)) reachedZ = false;

    if (reachedX) stepperX.runSpeed();
    if (reachedY) stepperY.runSpeed();
    if (reachedZ) stepperZ.runSpeed();

    if (!reachedX && !reachedY && !reachedZ) break;
  }
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperZ.setCurrentPosition(0);
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