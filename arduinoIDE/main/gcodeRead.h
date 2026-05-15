#include "sd.h"
#include "movemant.h"
extern sdCard sdc;
extern bool printing;
extern const int enx, eny;
float posX, posY, posZ, posE;
// float tarPosX, tarPosY, tarPosZ;
int F;

float getGcVal(int start, String line) {
  String value = "";

  // Find start of number
  while (start < line.length()) {
    char c = line[start];

    if ((c >= '0' && c <= '9') || c == '-' || c == '.') {
      break;
    }

    start++;
  }

  // Read number
  while (start < line.length()) {
    char c = line[start];

    if ((c >= '0' && c <= '9') || c == '-' || c == '.') {
      value += c;
      start++;
    }
    else {
      break;
    }
  }

  return value.toFloat();
}

void gcMove(String line, int g) {
  bool mx = false;
  bool my = false;
  bool mz = false;
  bool me = false;
  int X = line.indexOf("X");
  int Y = line.indexOf("Y");
  int Z = line.indexOf("Z");
  int E = line.indexOf("E");
  int F = line.indexOf("F");

  if (X != -1) {
    X = getGcVal(X + 1, line);
    mx = true;
  }
  if (Y != -1) {
    Y = getGcVal(Y + 1, line);
    my = true;
  }
  if (Z != -1) {
    Z = getGcVal(Z + 1, line);
    //mz = true;
  }
  if (E != -1) {
    E = getGcVal(E + 1, line);
    //me = true;
  }
  if (F != -1) {
    F = getGcVal(F + 1, line);
    maxSpeed = F;
  }
  else F = maxSpeed;

  // Serial.println("moving");
  moveTo(X, mx, Y, my, Z, mz, E, me, F);
}

void executeGCline(const char* path, int lineNum) {
  String line = sdc.readLine(path, lineNum);
  Serial.println("");
  Serial.print("Exexuting line: ''");
  Serial.print(line + 1);
  Serial.print("'' as line: ");
  Serial.println(lineNum);

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
    float g = getGcVal(gIdx, line);

    switch ((int)g) {
      //move
      case 0:
      case 1:
        gcMove(line, g);
        break;

      //set position
      case 92: {
        int X = line.indexOf("X");
        int Y = line.indexOf("Y");
        int Z = line.indexOf("Z");
        int E = line.indexOf("E");

        if (X != -1) posX = getGcVal(X + 1, line);
        if (Y != -1) posY = getGcVal(Y + 1, line);
        if (Z != -1) posZ = getGcVal(Z + 1, line);
        if (E != -1) posE = getGcVal(E + 1, line);
        break;
      }

      //return to home
      case 28:
        moveToHome();
        break;

      //fixed point/absolute cords
      case 90:
        reletiveCords = false;
        Serial.println("Cords mode set to absolute.");
        break;

      //offset/reletive cords
      case 91:
        reletiveCords = true;
        Serial.println("Cords mode set to reletive.");
        break;
    }

    return;
  }

  if (line.indexOf("M") != -1) {
    int m = line[line.indexOf("M") + 1];

    switch (m) {
      //stop program
      case 30:
        printing = false;
        break;

      //set bed temperature
      case 140: {
        int tprs = line.indexOf("S");
        float tprf = getGcVal(tprs, line);
        Serial.println("Setting bed temp: ");
        Serial.print(tprf);
        break;
      }

      //read bed and hotend temperatures
      case 105:
        Serial.println("Checking temps");
        break;

      //set bed temperature and wait
      case 190:
        Serial.println("Setting bed temp and waiting");
        break;

      //set hotend temperature
      case 104: {
        int tprs = line.indexOf("S");
        float hotendTargetTemp = getGcVal(tprs, line);
        Serial.println("Setting hotend temp");
        break;
      }

      //set hotend temperature and wait
      case 109: {
        int tprs = line.indexOf("S");
        float hotendTargetTemp = getGcVal(tprs, line);
        Serial.println("Setting hotend temp and waiting");
        break;
      }

      //extruder fixed cords
      case 82:
        break;

      //extruder offset cords
      case 83:
        break;

      case 18:
        Serial.println("Disabling motors");
        digitalWrite(enx, HIGH);
        digitalWrite(eny, HIGH);
        break;
    }

    return;
  }

  //unuidentified comand
  Serial.println("Unknown command/comment line: ");
  Serial.print(line);
  printing = false;
}