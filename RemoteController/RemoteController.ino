#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial hc05(0, 1);
int upButtonPin = 5;
int downButtonPin = 6;

LiquidCrystal_I2C lcd(0x3f, 16, 2);

int targetTemp = 70;

void setup() {
  hc05.begin(9600);
    pinMode(upButtonPin, INPUT);
    pinMode(downButtonPin, INPUT);
    lcd.init();
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
  if ((upButtonState == LOW) || (downButtonState == LOW)) {
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
    Serial.println("button is presseddd..");
  }
  lcd.setCursor(4, 1);
  lcd.print(targetTemp);
  Serial.println("loop running");
}
