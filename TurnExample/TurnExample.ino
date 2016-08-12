#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4LCD lcd;
L3G gyro;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

int turnSpeed = 150;
int motorSpeed = 250;

void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
}

// Turn left
void turnLeft(int degrees) {
  turnSensorReset();
  motors.setSpeeds(-turnSpeed, turnSpeed);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
  } while (angle < degrees);
  motors.setSpeeds(0, 0);
}

// Turn right
void turnRight(int degrees) {
  turnSensorReset();
  motors.setSpeeds(turnSpeed, -turnSpeed);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
  } while (angle > -degrees);
  motors.setSpeeds(0, 0);
}

void loop() {
  turnSensorUpdate();

  int angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
  lcd.gotoXY(0, 0);
  lcd.print(angle);
  lcd.print(" ");

  // If we press A, turn left.
  bool buttonPress = buttonA.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);
    turnLeft(90);
  }

  // If we press B, turn right
  buttonPress = buttonB.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);
    turnRight(90);
  }

  // If we press C, dance a jig
  buttonPress = buttonC.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);

    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(1000);

    motors.setSpeeds(0, 0);
    delay(500);

    turnRight(90);
    delay(500);

    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(1000);

    turnLeft(90);
    delay(500);

    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(1000);

    turnLeft(90);
    delay(500);  

    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(1000);          

    turnLeft(90);
    delay(500);  

    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(2000);         
    
    turnRight(180);
  }


}
