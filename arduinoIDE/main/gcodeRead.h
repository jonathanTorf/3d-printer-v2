#include "sd.h"
extern sdCard sdc;
extern bool printing;
float posX, posY, posZ;
int F;

float getGcVal(int start, String line) {
  String string = "";
  for (int i = start; i < line.length(); i++) {
    if (line[i] == " ") break;
    string += line[i];
  }
  return string.toFloat();
}

void gcMove(String line, int g) {
  int X = line[line.indexOf("X") + 1];
  int Y = line[line.indexOf("Y") + 1];
  int Z = line[line.indexOf("Z") + 1];
  int F = line[line.indexOf("F") + 1];

  if (X != -1) posX = getGcVal(X, line);
  if (Y != -1) posY = getGcVal(Y, line);
  if (Z != -1) posZ = getGcVal(Z, line);
  if (F != -1) F = getGcVal(F, line);

  //move function(when i make one) here.
}

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);
  int gIdx;

  //remove commants.
  int bracketPos = line.indexOf("(");
  if (bracketPos != -1) 
    line.remove(bracketPos, line.indexOf(")") - bracketPos + 1);
  
  //settings and movemant.
  gIdx = line[line.indexOf("G")];
  if (gIdx != -1) {
    int g = line[gIdx + 1];
    if (g == 0 || g == 1) gcMove(line, g);
  }

  //stop program.
  int m = line[line.indexOf("M") + 1];
  if (m == 30) printing = false;
}