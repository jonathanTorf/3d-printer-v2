#include "UI.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
UI::UI() {}

UI::begin() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("3D printer-V2");
  lcd.setCursor(0, 1);
  lcd.print("By Jonathan Torf");

  delay(2500);
  lcd.clear();
  lcd.print("3D printer-V2");
  lcd.setCursor(0, 1);
  lcd.print("> to select func");
}