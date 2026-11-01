#include <AccelStepper.h>

#define EN_PIN   45
#define STEP_PIN 46
#define DIR_PIN  47

// DRIVER mode: STEP + DIR
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup()
{
    pinMode(EN_PIN, OUTPUT);

    // A4988 enable is active LOW
    digitalWrite(EN_PIN, LOW);

    stepper.setMaxSpeed(200);
    stepper.setAcceleration(500);
}

void loop()
{
    stepper.runSpeed();
}