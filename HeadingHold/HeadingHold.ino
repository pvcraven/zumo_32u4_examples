#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

L3G gyro;
Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

// Motor speeds while turning
int turnSpeed = 160;

// Max motor speed
int motorSpeed = 450;

// Min motor speed as we get close
int minSpeed = 140;

// How fast to accelerate or deaccelerate
int acceleration = 2;

// How close do we need to be before slowing down
int slowDownDistance = 1400;

void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
  lcd.print("Press C");
}

// Going Forward
void forward(long count) {

  // Reset everything to zero
  turnSensorReset();
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();

  // Variables to keep track of stuff
  long countsLeft = 0;
  long countsRight = 0;
  int curSpeed = acceleration;
  
  // Loop until we get there
  while(countsLeft < count) {

    // --- Read sensor values
    // Wheel encoders for distance
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    // Heading
    turnSensorUpdate();
    int angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    int distanceLeft = count - countsLeft;

    // --- Calculate our speed
    // Not up to full speed, but a long way to go
    // Accelerate!
    if(curSpeed < motorSpeed && distanceLeft >= slowDownDistance) {
        curSpeed += acceleration;
        if(curSpeed > motorSpeed)
          curSpeed = motorSpeed;        
    }

    // Not up to min speed
    // Accelerate!
    else if(curSpeed < minSpeed) {
        curSpeed += acceleration;
        if(curSpeed > minSpeed)
          curSpeed = minSpeed;        
    } 

    // Getting close, and going fast
    // Slow down!
    else if(curSpeed > minSpeed) {
        curSpeed -= acceleration;
        if(curSpeed < minSpeed)
          curSpeed = minSpeed;        
      
    }

    // Set the motor speed.
    // We adjust the speed according to our angle so we keep the same heading.
    motors.setSpeeds(curSpeed + (angle * 5), curSpeed - (angle * 5));

    // Display
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
    lcd.gotoXY(0, 1);
    lcd.print(countsLeft);
    lcd.print(" ");
    delay(1);
  };

  // Full stop
  motors.setSpeeds(0, 0);
  delay(100);
}

// Turn left
void turnLeft(int degrees) {

  // Reset our turn sensor
  turnSensorReset();
  int cur_angle = 0;

  // Start turning
  motors.setSpeeds(-turnSpeed, turnSpeed);
  while (cur_angle < degrees) {
    turnSensorUpdate();
    cur_angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    lcd.gotoXY(0, 0);
    lcd.print(cur_angle);
    lcd.print(" ");

    // If we get close, slow down our turn rate
    if ( abs(degrees - cur_angle) < 25) {
      motors.setSpeeds(-turnSpeed / 2, turnSpeed / 2);
    }    
    delay(1);
  }

  // Stop
  motors.setSpeeds(0, 0);
  delay(100);
}

// Turn right
void turnRight(int degrees) {

  // Reset our turn sensor
  turnSensorReset();
  int cur_angle = 0;

  // Start turning
  motors.setSpeeds(turnSpeed, -turnSpeed);
  while (cur_angle > -degrees) {
    turnSensorUpdate();
    cur_angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    lcd.gotoXY(0, 0);
    lcd.print(cur_angle);
    lcd.print(" ");

    // If we get close, slow down our turn rate
    if ( abs(degrees - cur_angle) < 25) {
      motors.setSpeeds(turnSpeed / 2, -turnSpeed / 2);
    }    
    delay(1);
  }

  // Stop
  motors.setSpeeds(0, 0);
  delay(100);
}

void loop() {
  turnSensorUpdate();

  // If we press A, turn left.
  bool buttonPress = buttonA.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);
    turnLeft(90);
    lcd.clear();
  }

  // If we press A, turn right.
  buttonPress = buttonB.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);
    turnRight(90);
    lcd.clear();
  }


  // If we press C, dance a jig
  buttonPress = buttonC.getSingleDebouncedPress();
  if(buttonPress) {
    delay(500);

    forward(5000);
    
    turnRight(90);
    forward(5000);
    
    turnLeft(90);
    forward(5000);
    
    turnLeft(90);
    forward(5000);
    
    turnLeft(90);
    forward(5000);
    
    turnRight(90);
    forward(5000);
    
    turnRight(90);
    forward(5000);
    
    turnRight(90);
    forward(5000);
    
    turnRight(90);
    forward(10000);  
    
    turnRight(180);
  }  

}
