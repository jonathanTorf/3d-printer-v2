#include "Arduino.h"
#include "hotend.h"

hotend::hotend(int hep, int tp) {
  hotendPin = hep;
  thermistorPin = tp;
  pinMode(hotendPin, OUTPUT);
}

float hotend::getTemp() {
    int adc = analogRead(hotendPin);
    float voltage = adc * 5.0 / 1023.0;
    float resistance = 100000.0 * voltage / (5.0 - voltage);
    float temperatureK = 1.0 / (1.0 / 298.15 + log(resistance / 100000.0) / 3950.0);
    float temperatureC = temperatureK - 273.15;
    return(temperatureC);
}

hotend::updatePID(int sp) {
  float currantTime = millis() / 1000.0;
  float currantTemp = getTemp();
  float error = sp - currantTemp;
  float elapsedTime = currantTime - lastTime;
  float out = 0;
  float rateError = 0;

  if (error * cumError < 0) cumError = 0;
  else cumError += error * elapsedTime;
    
  if (elapsedTime > 0) {
      rateError = (error - lastError) / elapsedTime;
      out = error * kp + cumError * ki + rateError * kd;

      out = constrain(out, 0, 150);
      analogWrite(8, out);
  }

  lastError = error;
  lastTime = currantTime;

  Serial.print("Currant temp: ");
  Serial.print(currantTemp);
  Serial.print(", out: ");
  Serial.print(out);
  Serial.print(", p: ");
  Serial.print(error * kp);
  Serial.print(", i: ");
  Serial.print(cumError * ki);
  Serial.print(", d: ");
  Serial.println(rateError * kd);
}