#include "sd.h"
extern sdCard sdc;
float posX, posY, posZ;
int F;

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);

  int bracketPos = line.indexOf("(");
  if (bracketPos != -1) 
    line.remove(bracketPos, line.indexOf(")") - bracketPos + 1);

}

float getGcVal(int start, String line) {
  String string = "";
  for (int i = start; i < line.length(); i++) {
    if (line[i] == " ") break;
    string += line[i];
  }
  return string.toFloat();
}

void gcMove(String line) {
  int X = line[line.indexOf("X") + 1];
  int Y = line[line.indexOf("Y") + 1];
  int Z = line[line.indexOf("Z") + 1];
  int F = line[line.indexOf("F") + 1];
  int g = line[line.indexOf("G") + 1];

  if (X != -1) posX = getGcVal(X, line);
  if (Y != -1) posY = getGcVal(Y, line);
  if (Z != -1) posZ = getGcVal(Z, line);
  if (F != -1) F = getGcVal(F, line);

  //move function(when i make one) here.
}