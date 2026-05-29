#ifndef PRINTER_H
#define PRINTER_H

class printer {
  private:
    const int lsx = 2;
    const int lsy = 3;
    const int enx = 12;
    const int eny = 7;

    const int funcAmt = 0;

    const bool skipHoming = false;
    const char* path = "TC.gx";
    bool printing = true;

  public:
    printer();
    begin();
    selectFunction();
    selectPath();
    print(const char* path);
};

#endif