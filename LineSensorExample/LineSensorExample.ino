#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;

// Sensor values will go in here
unsigned int lineSensorValues[3];

void setup() {
  // put your setup code here, to run once:
  lineSensors.initThreeSensors();
  lineSensors.emittersOn();
}

void loop() {
  lineSensors.read(lineSensorValues);
  lcd.gotoXY(0, 0);
  lcd.print(lineSensorValues[0] / 10);
  lcd.print(" ");
  lcd.print(lineSensorValues[1] / 10);
  lcd.print(" ");
  lcd.gotoXY(0, 1);
  lcd.print(lineSensorValues[2] / 10);
  lcd.print(" ");
}
