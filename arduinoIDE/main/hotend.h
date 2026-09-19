#ifndef HOTEND_H
#define HOTEND_H

class hotend {
  private:
    int hotendPin;
    int thermistorPin;
    float kp = 10;
    float ki = 0.3;
    float kd = 3;

    long lastTime = 0;
    float cumError = 0;
    float lastError = 0;

  public:
    hotend(int hep, int tp);
    float getTemp();
    updatePID(int sp);
};

#endif