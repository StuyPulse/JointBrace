#include <SoftwareSerial.h>

SoftwareSerial hc06(-1,-1);

int sensorPin = -1;
int heatingPin = -1;
int targetTemp = 70;

void setup() {
  Serial.begin(9600);
  pinMode(heatingPin, OUTPUT);
  pinMode(sensorPin, INPUT);
   
  hc06.begin(9600);
}

void setTargetTemp() {
  if (hc06.available()){
    targetTemp = hc06.read();
   
    
  }
}
int getTargetTemp() {
  printf("getting target temp");
  return targetTemp;
}

int getTemperature() {
    int reading = analogRead(sensorPin);  
  
    // converting that reading to voltage, for 3.3v arduino use 3.3
     float voltage = reading * 5.0;
     voltage /= 1024.0; 
 
      // print out the voltage
    Serial.print(voltage); Serial.println(" volts");
 
      // now print out the temperature
     float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 
      // now convert to Fahrenheit
     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    Serial.print(temperatureF); Serial.println(" degrees F");
    return temperatureF;
}

void setTemperatureSwitch(bool value) {
  printf("setting temp");
  if (value) {
    analogWrite(heatingPin, 255);
    } else{
      analogWrite(heatingPin, 0);
      } 
}

void controlTemperature() {
  if (getTemperature() < getTargetTemp()) {
    setTemperatureSwitch(true);
  } else {
    setTemperatureSwitch(false);
  }
}



void loop() {
  controlTemperature();
  delay(5000);
}
