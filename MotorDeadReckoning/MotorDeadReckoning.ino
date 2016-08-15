#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
// Documentation for the motors class:
// http://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_motors.html
Zumo32U4Motors motors;

const uint16_t motorSpeed = 300;

void setup() {
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press A");
}

void loop() {

  // Wait for a button press
  bool buttonPress = buttonA.getSingleDebouncedPress();
  
  if (buttonPress) {
    // Wait
    delay(1000);

    // Move forward for two seconds
    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(2000);

    // Stop and pause
    motors.setSpeeds(0, 0);
    delay(500);

    // Move backwards two seconds
    motors.setSpeeds(-motorSpeed, -motorSpeed);
    delay(2000);

    // Stop
    motors.setSpeeds(0, 0);
    delay(500);

    // Turn left
    motors.setSpeeds(-motorSpeed, motorSpeed);
    delay(1000);    

    // Stop
    motors.setSpeeds(0, 0);
  }
}
