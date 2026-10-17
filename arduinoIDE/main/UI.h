#ifndef UI_H
#define UI_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

class UI {
  public:
    UI();
    begin();
    printFunction(int func);
    int selectFrom(String *options, int totalOptions, bool verticalSelect = true);
};

#endif