#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

const uint16_t motorSpeed = 200;

void setup() {
  lcd.clear();
}

void loop() {

  // Wait for a button press
  bool buttonPress = buttonA.getSingleDebouncedPress();
  
  if (buttonPress) {
    // Wait
    delay(1000);

    // Move forward for three seconds
    motors.setSpeeds(motorSpeed, motorSpeed);
    delay(3000);

    // Stop and pause
    motors.setSpeeds(0, 0);
    delay(500);

    // Move backwards three seconds
    motors.setSpeeds(-motorSpeed, -motorSpeed);
    delay(3000);

    // Stop
    motors.setSpeeds(0, 0);
  }
}
