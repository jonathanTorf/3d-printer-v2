#include "Arduino.h"
#include "hotend.h"

hotend::hotend(int hep, int tp) {
  hotendPin = hep;
  thermistorPin = tp;
  pinMode(hotendPin, OUTPUT);
  analogWrite(hotendPin, 0);
}

float hotend::getTemp() {
    int adc = analogRead(thermistorPin);
    float voltage = adc * 5.0 / 1023.0;
    float resistance = 100000.0 * voltage / (5.0 - voltage);
    float temperatureK = 1.0 / (1.0 / 298.15 + log(resistance / 100000.0) / 3950.0);
    float temperatureC = temperatureK - 273.15;
    return(temperatureC);
}

void hotend::updatePID(int sp) {
  float currantTime = millis() / 1000.0;
  float currantTemp = getTemp();
  float error = sp - currantTemp;
  float elapsedTime = currantTime - lastTime;
  int out = 0;
  float rateError = 0;

  if (currantTemp < 0 || currantTemp > 350) {
    Serial.print("currantTemp is outside valid range, skipping PID itiration: ");
    Serial.println(currantTemp);
    delay(100);
    return;
  }

  if (error * lastError < 0) cumError = 0;
  else cumError += error * elapsedTime;
    
  if (elapsedTime > 0) {
      rateError = (error - lastError) / elapsedTime;
      out = error * kp + cumError * ki + rateError * kd;

      out = constrain(out, 0, 255);
      // analogWrite(hotendPin, out);
      int time = out * 5;
      digitalWrite(hotendPin, HIGH);
      delay(time);
      digitalWrite(hotendPin, LOW);
      delay(255 * 5 - time);
  }

  lastError = error;
  lastTime = currantTime;

  Serial.print("Time: ");
  Serial.print(currantTime);
  Serial.print(", Currant temp: ");
  Serial.print(currantTemp);
  Serial.print(" / ");
  Serial.print(sp);
  Serial.print(", out: ");
  Serial.print(out);
  Serial.print(", p: ");
  Serial.print(error * kp);
  Serial.print(", i: ");
  Serial.print(cumError * ki);
  Serial.print(", d: ");
  Serial.println(rateError * kd);
}

void hotend::waitForTemp(int temp) {
  int currantTemp = getTemp();
  int lastTemp = 0;

  Serial.print("Waiting for temp: ");
  Serial.println(temp);
  while ((int)currantTemp != (int)lastTemp && currantTemp != temp) {
    currantTemp = getTemp();
    updatePID(temp);
    lastTemp = currantTemp;
  }
  Serial.print("Target temp acheaved, target: ");
  Serial.print(temp);
  Serial.print(", currant: ");
  Serial.println(getTemp());
}