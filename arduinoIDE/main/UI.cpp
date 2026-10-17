#include "WString.h"
#include "UI.h"
#include "joystick.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
UI::UI() {}

const String functions[] = {"Print: [,]slt", "Home: [,]slt", "Move axis:[,]slt"};

UI::begin() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("3D printer-V2");
  lcd.setCursor(0, 1);
  lcd.print("By Jonathan Torf");

  delay(1000);
  lcd.clear();
  lcd.print("3D printer-V2");
  lcd.setCursor(0, 1);
  lcd.print("[>]select func");
}

UI::printFunction(int func) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(functions[func]);
}

int UI::selectFrom(String *options, int totalOptions, bool verticalSelect = true) { 
    int opt = 0; 
    
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(options[opt]);

    while (true) {
        int move = jStick.reletiveDir(verticalSelect); 

        if (move != 0) {
            opt -= move;            
            if (opt < 0) opt = 0;
            if (opt >= totalOptions) opt = totalOptions - 1;
            Serial.println(opt);

            lcd.setCursor(0, 1);
            lcd.print("                ");
            lcd.setCursor(0, 1);
            lcd.print(options[opt]);

            while (jStick.reletiveDir(verticalSelect) != 0) { delay(50); }
        }

        if (jStick.reletiveDir(!verticalSelect) == 1) {
            while (jStick.reletiveDir(!verticalSelect) == 1) { delay(50); }
            return opt;
        }
        delay(50);
    }
}
