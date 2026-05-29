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

sdCard::listGXFiles(const char* folder = "/") {
  File dir = SD.open(folder);

  if (!dir) {
    Serial.println("Failed to open directory");
    return;
  }

  if (!dir.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  Serial.println("GX files found:");

  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;

    if (!entry.isDirectory()) {
      String name = entry.name();

      // convert to lowercase for safe matching
      name.toLowerCase();

      if (name.endsWith(".gx")) {
        Serial.print(" - ");
        Serial.println(entry.name());
      }
    }

    entry.close();
  }

  dir.close();
}