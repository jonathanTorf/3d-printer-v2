#ifndef PRINTER_H
#define PRINTER_H

class printer {
  private:
    const int funcAmt = 2;
    const char* path = "TC.gx";
    bool printing = true;

  public:
    printer();
    begin();
    selectFunction();
    selectPath();
    print();
};

extern const int lsx;
extern const int lsy;
extern const int lsz;
extern const int enx;
extern const int eny;
extern const int enz;
// extern joystick joystick;

extern bool printing;
extern const bool skipHoming;

#endif