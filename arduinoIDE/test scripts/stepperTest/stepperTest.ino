#include <AccelStepper.h>

#define EN_PIN   24
#define STEP_PIN 23
#define DIR_PIN  22

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup()
{
    Serial.begin(9600);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);

    stepper.setMaxSpeed(2000);
    stepper.setSpeed(500);
}

void loop()
{
    stepper.runSpeed();
    // Serial.println("test");
}