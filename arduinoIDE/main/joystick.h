#ifndef joystick_h
#define joystick_h

class joystick {
  private:
    int base = 480;
    int th = 100;
    int xMult = -1;
    int yMult = 1;

    int sw;
    int vrx;
    int vry;

  public:
    joystick(int s, int x, int y);
    begin();
    int getDirX();
    int getDirY();
    bool pressed();
};

#endif