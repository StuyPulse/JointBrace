#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial hc05(2, 3);
int upButtonPin = 5;
int downButtonPin = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int targetTemp = 70;
int upButtonState = 0;
int downButtonState = 0;

void setup() {
  Serial.begin(9600);
  hc05.begin(9600);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Please work");
  lcd.setCursor(4,1);
}

void changeTargetTemp() {
/* if up is pressed, increase*/
  upButtonState = digitalRead(upButtonPin);
  downButtonState = digitalRead(downButtonPin);
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
  upButtonState = digitalRead(upButtonPin);
  downButtonState = digitalRead(downButtonPin);
  Serial.println(upButtonState);
  Serial.println(downButtonState);
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
  }
  lcd.setCursor(4, 1);
  lcd.print(targetTemp);
}
