#include <AccelStepper.h>

#define EN_PIN   24
#define STEP_PIN 23
#define DIR_PIN  22

const int ms1 = 39;
const int ms2 = 40;
const int ms3 = 41;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup()
{
    digitalWrite(ms1, LOW);
    digitalWrite(ms2, LOW);
    digitalWrite(ms3, LOW);

    Serial.begin(9600);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);

    stepper.setMaxSpeed(2000);
    stepper.setSpeed(1000);
}

void loop()
{
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(5);
}