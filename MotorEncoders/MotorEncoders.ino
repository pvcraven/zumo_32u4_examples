#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;

const uint16_t motorSpeed = 250;

void setup() {
  lcd.clear();
}

void forward(long count) {
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  long countsLeft = 0;
  long countsRight = 0;
  motors.setSpeeds(motorSpeed, motorSpeed);
  while(countsLeft < count) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();
    lcd.gotoXY(0, 1);
    lcd.print(countsLeft);
    lcd.print(" ");
    delay(2);
  };
  
  motors.setSpeeds(0, 0);
}

void reverse(long count) {
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  long countsLeft = 0;
  long countsRight = 0;
  motors.setSpeeds(-motorSpeed, -motorSpeed);
  while(countsLeft < count) {
    countsLeft -= encoders.getCountsAndResetLeft();
    countsRight -= encoders.getCountsAndResetRight();
    lcd.gotoXY(0, 1);
    lcd.print(countsLeft);
    lcd.print(" ");
    delay(2);
  };
  
  motors.setSpeeds(0, 0);
}
void loop() {

  // Wait for a button press
  bool buttonPress = buttonA.getSingleDebouncedPress();
  
  if (buttonPress) {
    // Wait
    delay(1000);
    forward(5000);
    delay(1000);
    reverse(5000);
  }
}
