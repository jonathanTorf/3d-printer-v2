#include "sd.h"
#include "gcodeRead.h"

sdCard sdc(53);
const char* path = "test.txt";
bool printing = false;

void setup() {
  Serial.begin(9600);
  Serial.println("program starting");

  sdc.begin();
  Serial.println(sdc.readLine("test.txt", 0));
  sdc.writeLine("test.txt", 2, "deez nuts");
  Serial.println(sdc.readLine("test.txt", 2));

  printing = true;
  executeGCline(path, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
