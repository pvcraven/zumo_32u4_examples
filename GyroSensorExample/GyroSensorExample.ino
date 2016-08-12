#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4LCD lcd;
L3G gyro;
Zumo32U4ButtonA buttonA;

// Sensor values will go in here
unsigned int lineSensorValues[3];

void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
}

void loop() {
  turnSensorUpdate();

  lcd.gotoXY(0, 0);
  int angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
  lcd.print(angle);
    
  lcd.print(" ");

}
