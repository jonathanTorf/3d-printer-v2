#include "sd.h"
#include <Arduino.h>

sdCard::sdCard(int cs) { csPin = cs; }

sdCard::begin() {
  pinMode(csPin, OUTPUT);
    if (!SD.begin(csPin)) {
      Serial.println("SD init failed!");
    } else {
      Serial.println("SD init success!");
    }
}

String sdCard::readLine(const char* path, int targetLine) {
      File file = SD.open(path);

      if (!file) {
        Serial.println("Failed to open file");
        return "";
      }

      int currentLine = 0;
      String line = "";

      while (file.available()) {
        char c = file.read();

        if (c == '\n') {
          if (currentLine == targetLine) {
            file.close();
            return line;
          }
          currentLine++;
          line = "";
        } else {
          line += c;
        }
      }

      if (currentLine == targetLine) {
        file.close();
        return line;
      }

      file.close();
      return "";
    }

sdCard::writeLine(const char* path, int targetLine, String newLine) {
      File file = SD.open(path);

      if (!file) {
        Serial.println("Failed to open file for reading");
        return;
      }

      String tempContent = "";
      int currentLine = 0;
      String line = "";

      while (file.available()) {
        char c = file.read();

        if (c == '\n') {
          if (currentLine == targetLine) {
            tempContent += newLine + "\n";
          } else {
            tempContent += line + "\n";
          }
          line = "";
          currentLine++;
        } else {
          line += c;
        }
      }

      if (line.length() > 0) {
        if (currentLine == targetLine) {
          tempContent += newLine + "\n";
        } else {
          tempContent += line + "\n";
        }
        currentLine++;
      }

      file.close();

      while (currentLine <= targetLine) {
        if (currentLine == targetLine) {
          tempContent += newLine + "\n";
        } else {
          tempContent += "\n";
        }
        currentLine++;
      }

      SD.remove(path);

      File newFile = SD.open(path, FILE_WRITE);

      if (newFile) {
        newFile.print(tempContent);
        newFile.close();
      } else {
        Serial.println("Failed to write file");
      }
    }

int sdCard::getGXFiles(const char* path, String outFiles[], int maxFiles = 20) {
  File dir = SD.open(path);
  if (!dir) return -1;

  int count = 0;

  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;

    String name = entry.name();

    // Skip folders
    if (entry.isDirectory()) {
      entry.close();
      continue;
    }

    // Check for ".gx"
    if (name.endsWith(".gx")) {
      if (count < maxFiles) {
        outFiles[count] = name;
        count++;
      }
    }

    entry.close();
  }

  dir.close();
  return count;
}

int sdCard::countLines(const char* path) {
  File file = SD.open(path);

  if (!file) {
    Serial.println("Failed to open file");
    return -1;
  }

  int lines = 0;
  bool hasData = false;
  char lastChar = '\0';

  while (file.available()) {
    char c = file.read();
    hasData = true;
    lastChar = c;

    if (c == '\n') {
      lines++;
    }
  }

  file.close();

  if (hasData && lastChar != '\n') {
    lines++;
  }

  return lines;
}