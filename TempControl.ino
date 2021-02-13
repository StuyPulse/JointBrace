int getTargetTemp() {
  printf("getting target temp");
  return 70;
}

int getTemperature() {
  printf("getting temp");
  return 65;
}

void setTemperatureSwitch(bool value) {
  printf("setting temp");
}

void controlTemperature() {
  if (getTemperature() < getTargetTemp()) {
    setTemperatureSwitch(true);
  } else {
    setTemperatureSwitch(false);
  }
}

void setup() {
}

void loop() {
  controlTemperature();
  delay(5000);
}
