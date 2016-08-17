/*
 * Move and avoid example
 *
 * Video Explanation: https://youtu.be/mv8Kxi9K_sY
 */

// --- Includes ---

#include <Wire.h> // Used for Accelerometer
#include <Zumo32U4.h>
#include "TurnSensor.h"

// --- Robot Components ---

Zumo32U4LCD lcd;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
LSM303 lsm303; // Accelerometer
L3G gyro;

// --- Enums ---

// This enum is used for our "state machine."
enum State {
  pause_state,
  forward_left_state,
  forward_right_state,
  scan_left_state,
  scan_right_state,
  reverse_state,
  forward_state
};

// --- Constants ---

const uint16_t motorSpeed = 350;
const uint16_t turnSpeed = 200;
const int acceleration = 2;

// --- Global Variables ---

State state = pause_state;
int curSpeed = 0;

// --- Support Functions ---

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

// Stop
void stop() {
  motors.setSpeeds(0, 0);
}

// Go forward
void forward() {
  // Get out heading
  turnSensorUpdate();
  int angle = (((int32_t)turnAngle >> 16) * 360) >> 16;

  // Move foward, adjusting motor speed to hold heading
  motors.setSpeeds(curSpeed + (angle * 5), curSpeed - (angle * 5));
}

// Back up!
void reverse() {
  motors.setSpeeds(-motorSpeed, -motorSpeed);
}

// Look left
void scanLeft() {
  motors.setSpeeds(-curSpeed, curSpeed);
}

// Look right
void scanRight() {
  motors.setSpeeds(curSpeed, -curSpeed);
}

// Veer to the left
void forwardLeft() {
  motors.setSpeeds(curSpeed / 2, curSpeed);
}

// Veer to the right
void forwardRight() {
  motors.setSpeeds(curSpeed, curSpeed / 2);
}

// --- Setup ---
void setup() {

  // Proximity sensors
  proxSensors.initThreeSensors();

  // Accelerometer
  Wire.begin();
  lsm303.init();
  lsm303.enableDefault();

  // Gyrometer
  turnSensorSetup();
  delay(500);
  turnSensorReset();
}

// --- Main Loop ---
void loop() {

  // --- Read Sensors

  // Buttons
  bool buttonPress = buttonA.getSingleDebouncedPress();

  // Proximity sensors
  proxSensors.read();

  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int centerLeftSensor = proxSensors.countsFrontWithLeftLeds();
  int centerRightSensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();

  // Accelerometer
  lsm303.read();
  int16_t x = lsm303.a.x;
  int16_t y = lsm303.a.y;
  int32_t magnitudeSquared = (int32_t)x * x + (int32_t)y * y;

  // --- Change states
  if (state == pause_state) {
    if (buttonPress) {
      state = forward_state;
      turnSensorReset();
    }
  }
  else if (buttonPress) {
    state = pause_state;
  }
  else if (magnitudeSquared > 250000000) {
    state = reverse_state;
  }
  else if (state == scan_left_state) {
    if (centerLeftSensor < 4 && centerRightSensor < 4) {
      state = forward_state;
      turnSensorReset();
    }
  }
  else if (state == scan_right_state) {
    if (centerLeftSensor < 4 && centerRightSensor < 4) {
      state = forward_state;
      turnSensorReset();
    }
  }
  else if (state == forward_state) {
    if (centerLeftSensor >= 5 && centerRightSensor >= 5) {
      if (centerLeftSensor < centerRightSensor) {
        state = scan_left_state;
      } else {
        state = scan_right_state;
      }
    }
    else if (centerLeftSensor >= 2 && centerRightSensor >= 2) {
      if (centerLeftSensor < centerRightSensor) {
        state = forward_left_state;
      } else {
        state = forward_right_state;
      }
    }
  }
  else if (state == forward_left_state || state == forward_right_state) {
    if (centerLeftSensor < 2 && centerRightSensor < 2) {
      state = forward_state;
      turnSensorReset();
    }
    if (centerLeftSensor >= 5 && centerRightSensor >= 5) {
      if (centerLeftSensor < centerRightSensor) {
        state = scan_left_state;
      } else {
        state = scan_right_state;
      }
    }
  }

  // --- Set motor speed

  if (state != pause_state && curSpeed < motorSpeed) {
    curSpeed += acceleration;
  }

  if (state == pause_state) {
    stop();
    curSpeed = 0;
  }
  else if (state == forward_state)
    forward();
  else if (state == forward_left_state)
    forwardLeft();
  else if (state == forward_right_state)
    forwardRight();
  else if (state == scan_left_state)
    scanLeft();
  else if (state == scan_right_state)
    scanRight();
  else if (state == reverse_state) {
    lcd.gotoXY(0, 0);
    lcd.print("Reverse   ");
    reverse();
    delay(250);
    turnLeft(135);
    curSpeed = 0;
    delay(250);
    state = forward_state;
    lcd.clear();
    turnSensorReset();
  }

  // --- Display
  lcd.gotoXY(0, 0);
  if (state == pause_state)
    lcd.print("Stop     ");
  else if (state == forward_state)
    lcd.print("Forward  ");
  else if (state == forward_left_state)
    lcd.print("Left     ");
  else if (state == forward_right_state)
    lcd.print("Right     ");
  else if (state == scan_left_state)
    lcd.print("Scan Left ");
  else if (state == scan_right_state)
    lcd.print("Scan Right");

  lcd.gotoXY(0, 1);
  lcd.print(left_sensor);
  lcd.print(" ");
  lcd.print(centerLeftSensor);
  lcd.print(" ");
  lcd.print(centerRightSensor);
  lcd.print(" ");
  lcd.print(right_sensor);

  delay(2);
}
