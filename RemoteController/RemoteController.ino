#include <SoftwareSerial.h>

SoftwareSerial hc05(-1,-1);
int upButtonPin = -1;
int downButtonPin = -1;


int targetTemp = 70;

void setup() {
  hc05.begin(9600);
    pinMode(upButtonPin, INPUT);
    pinMode(downButtonPin, INPUT);
}

void changeTargetTemp() {
/* if up is pressed, increase*/
  bool upButtonState = digitalRead(upButtonPin);
  bool downButtonState = digitalRead(downButtonPin);
  if (upButtonState == LOW) {
    targetTemp++;
    Serial.println("incrementing temperature by 1...");
  }
  else if (downButtonState == LOW) {
    targetTemp--;
    Serial.println("decrementing temperature by 1...");
  }
}

bool isButtonPressed() {
  bool upButtonState = digitalRead(upButtonPin);
  bool downButtonState = digitalRead(downButtonPin);
  if ((upButtonState == LOW) || (downButtonState == Low)) {
    Serial.println("A button is pressed");
    return true;
  }
  else {
    return false;
  }
} 

void loop() {
  if (isButtonPressed()) {
    changeTargetTemp();
    hc05.write(targetTemp);
    delay(1000);
    Serial/println("Running..");
  }
  
}

