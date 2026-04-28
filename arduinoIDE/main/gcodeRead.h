#include "sd.h"
#include "movemant.h"
extern sdCard sdc;
extern bool printing;
float posX, posY, posZ, posE;
float tarPosX, tarPosY, tarPosZ;
int F;

float getGcVal(int start, String line) {
  String value = "";

  // Skip spaces (just in case)
  while (start < line.length() && line[start] == ' ') {
    start++;
  }

  // Read valid number characters
  for (int i = start; i < line.length(); i++) {
    char c = line[i];

    if ((c >= '0' && c <= '9') || c == '-' || c == '.') {
      value += c;
    } else {
      break; // stop at first non-number character
    }
  }

  // Validate result
  if (value.length() == 0) {
    // Serial.println("No number found");
    return -1;
  }

  return value.toFloat();
}

void gcMove(String line, int g) {
  int X = line.indexOf("X");
  int Y = line.indexOf("Y");
  int Z = line.indexOf("Z");
  int E = line.indexOf("E");
  int F = line.indexOf("F");

  if (X != -1) tarPosX = getGcVal(X + 1, line);
  if (Y != -1) tarPosY = getGcVal(Y + 1, line);
  if (Z != -1) tarPosZ = getGcVal(Z + 1, line);
  if (F != -1) F = getGcVal(F + 1, line);
  if (E != -1) E = getGcVal(E + 1, line);

  Serial.println("moving");
  //move function(when i make one) here.
}

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);
  //Serial.println(line);

  //remove commants.
  int bracketPos = line.indexOf("(");
  if (bracketPos != -1) {
    line.remove(bracketPos, line.indexOf(")") - bracketPos + 1);
    Serial.println("removing comment (()) ");
    Serial.print(line);
  }

  int semiCPos = line.indexOf(";");
  if (semiCPos != -1) {
    line.remove(semiCPos, line.length());
    Serial.println("removing comment (;) ");
    Serial.print(line);
  }

  int gIdx = line.indexOf("G");
  
  if (gIdx != -1) {
    float g = getGcVal(gIdx + 1, line);
    Serial.println(g);
    //move
    if (g == 0 || g == 1) gcMove(line, g);
    //set position
    else if (g == 92) {
      int X = line.indexOf("X");
      int Y = line.indexOf("Y");
      int Z = line.indexOf("Z");
      int E = line.indexOf("E");

      if (X != -1) posX = getGcVal(X + 1, line);
      if (Y != -1) posY = getGcVal(Y + 1, line);
      if (Z != -1) posZ = getGcVal(Z + 1, line);
      if (E != -1) posE = getGcVal(E + 1, line);
    }
    //return to home
    else if (g == 28) {
      
    }
    //fixed point cords
    else if (g == 90) {

    }
    //offset cords
    else if (g == 91) {

    }
    return;
  }

  if (line.indexOf("M") != -1) {
    int m = line[line.indexOf("M") + 1];
    //stop program
    if (m == 30) printing = false;
    //set bed temperature
    else if (m == 140) {
      int tprs = line.indexOf("S");
      float tprf = getGcVal(tprs, line);
      Serial.println("Setting bed temp: ");
      Serial.print(tprf);
      //set a bed target temp value to tprst
    }
    //read bed and hotend temperatures
    else if (m == 105) {
      Serial.println("Checking temps");
    }
    //set bed temperature and wait
    else if (m == 190) {
      Serial.println("Setting bed temp and waiting");
    }
    //set hotend temperature
    else if (m == 104) {
      int tprs = line.indexOf("S");
      float hotendTargetTemp = getGcVal(tprs, line);
      Serial.println("Setting hotend temp");
    }
    //set hotend temperature and wait
    else if (m == 109) {
      int tprs = line.indexOf("S");
      float hotendTargetTemp = getGcVal(tprs, line);
      Serial.println("Setting hotend temp and waiting");
    }
    //extruder fixed cords
    else if (m == 82) {

    }
    //extruder offset cords
    else if (m == 83) {
      
    }
    return;
  }

    //unuidentified comand
    Serial.println("Unknown command/comment line: ");
    Serial.print(line);
    printing = false;
}