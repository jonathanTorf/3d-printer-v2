#include <AccelStepper.h>

AccelStepper stepperY(AccelStepper::DRIVER, 11, 10);

int maxSpeed = 1000;
int acceleration = 500;
float defultSpeed = 500;

void movemantInit() {
  stepperY.setMaxSpeed(maxSpeed);
  stepperY.setAcceleration(acceleration);
}

void moveToHome() {
  stepperY.setSpeed(defultSpeed);

  while (true) {
    stepperY.runSpeed();

    delay(10);
  }
}