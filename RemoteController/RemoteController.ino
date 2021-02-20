#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial hc05(-1,-1);
int upButtonPin = -1;
int downButtonPin = -1;

const int rs = -1, en = -1, d4 = -1, d5 = -1, d6 = -1, d7 = -1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int targetTemp = 70;

void setup() {
  hc05.begin(9600);
    pinMode(upButtonPin, INPUT);
    pinMode(downButtonPin, INPUT);
    lcd.begin(16, 2);
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
    //"LOW" means button is pressed
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
    delay(1000);//slows down how much clicks registered
    Serial.println("Running..");
  }
  lcd.setCursor(4, 1);
  lcd.print(targetTemp);
}
