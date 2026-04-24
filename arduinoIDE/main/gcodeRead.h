#include "sd.h"
extern sdCard sdc;
extern bool printing;
float posX, posY, posZ, posE;
float tarPosX, tarPosY, tarPosZ;
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
  int X = line[line.indexOf("X")];
  int Y = line[line.indexOf("Y")];
  int Z = line[line.indexOf("Z")];
  int F = line[line.indexOf("F")];

  if (X != -1) tarPosX = getGcVal(X + 1, line);
  if (Y != -1) tarPosY = getGcVal(Y + 1, line);
  if (Z != -1) tarPosZ = getGcVal(Z + 1, line);
  if (F != -1) F = getGcVal(F + 1, line);

  //move function(when i make one) here.
}

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);
  int gIdx;

  //remove commants.
  int bracketPos = line.indexOf("(");
  if (bracketPos != -1) 
    line.remove(bracketPos, line.indexOf(")") - bracketPos + 1);
  int semiCPos = line.indexOf(";");
  if (semiCPos != -1) 
    line.remove(semiCPos, line.length());
  
  //movemant.
  gIdx = line[line.indexOf("G")];
  if (gIdx != -1) {
    int g = line[gIdx + 1];
    //move
    if (g == 0 || g == 1) gcMove(line, g);
    //set position
    if (g == 92) {
      int X = line[line.indexOf("X")];
      int Y = line[line.indexOf("Y")];
      int Z = line[line.indexOf("Z")];
      int E = line[line.indexOf("E")];

      if (X != -1) posX = getGcVal(X + 1, line);
      if (Y != -1) posY = getGcVal(Y + 1, line);
      if (Z != -1) posZ = getGcVal(Z + 1, line);
      if (E != -1) posE = getGcVal(E + 1, line);
    }
    //return to home
    if (g == 28) {
      
    }
  }

  if (line.indexOf("M") != -1) {
    int m = line[line.indexOf("M") + 1];
    //stop program
    if (m == 30) printing = false;
    //set bed temperature
    if (m == 140) {
      int tprs = line.indexOf("S");
      float tprf = getGcVal(tprs, line);
      //set a bed target temp value to tprst
    }
    //read bed and hotend temperatures
    if (m == 105) {
      
    }
    //set bed temperature and wait
    if (m == 190) {

    }
    //set hotend temperature
    if (m == 104) {
      int tprs = line.indexOf("S");
      float hotendTargetTemp = getGcVal(tprs, line);
    }
    //set hotend temperature and wait
    if (m == 109) {
      int tprs = line.indexOf("S");
      float hotendTargetTemp = getGcVal(tprs, line);
    }
  }
}