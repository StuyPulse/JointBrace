#include <SoftwareSerial.h>

SoftwareSerial hc06(-1,-1);

int sensorPin = -1;
int heatingPin = -1;
int targetTemp = 70;

void setup() {
  Serial.begin(9600);
  pinMode(heatingPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  hc06.begin(9600); //hc06 is the bluetooth module we use, 9600 is bytes sent
  Serial.println(" setting up");
}

void setTargetTemp() {
  if (hc06.available()){
    targetTemp = hc06.read();
    Serial.println('reading temp');
    Serial.println(targetTemp);
  }
}

int getTargetTemp() {
  Serial.println("getting target temp");
  return targetTemp;
}

int getTemperature() {
    int reading = analogRead(sensorPin);  
  
    // converting that reading to voltage, for 3.3v arduino use 3.3
     float voltage = reading * 5.0;
     voltage /= 1024.0; 
 
      // print out the voltage
    Serial.println(voltage); Serial.println(" volts");
 
      // now print out the temperature
     float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 
      // now convert to Fahrenheit
     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    Serial.println(temperatureF); Serial.println(" Degrees F");
    return temperatureF;
}

void setTemperatureSwitch(bool value) {
  if (value) {
    analogWrite(heatingPin, 255); //turns heat on full power
    Serial.println("Heating Turning On...");
    } else {
      analogWrite(heatingPin, 0);//turns it off
      Serial.println("Heating Turning Off");
    }
}

void controlTemperature() {
  if (getTemperature() < getTargetTemp()) {
    setTemperatureSwitch(true);
    Serial.println("Heating...");
  } else {
    setTemperatureSwitch(false);
    Serial.println("Reached Target Temperature");
  }
}

void loop() {
  //controlTemperature();
  //delay(5000);//delays speed temperature changes
  setTargetTemp();
}
