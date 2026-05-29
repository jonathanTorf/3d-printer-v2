#ifndef SD_HELPER_H
#define SD_HELPER_H

#include <SPI.h>
#include <SD.h>

class sdCard {
  private:
    int csPin;

  public:
    sdCard(int cs);
    begin();
    String readLine(const char* path, int targetLine);
    writeLine(const char* path, int targetLine, String newLine);
};

#endif