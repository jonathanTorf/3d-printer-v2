#include "sd.h"
extern sdCard sdc;

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);

  int bracketPos = line.indexOf("(");
  if (bracketPos != -1) {
    line.remove(bracketPos, line.indexOf(")") - bracketPos + 1);
  }
}