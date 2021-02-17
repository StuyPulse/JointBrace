#include <SoftwareSerial.h>

SoftwareSerial hc05(-1,-1);

int targetTemp = 70;

void setup() {
  hc05.begin(9600);
}

bool isButtonPressed() {
   return true;
  } 

void loop() {
  if (isButtonPressed()) {
    hc05.write(targetTemp);
  }
}
