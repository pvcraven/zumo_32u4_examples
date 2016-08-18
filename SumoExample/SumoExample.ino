/*
 * Very dumb sumo robot example.
 * 
 * Hopefully this can get you started. The robot just
 * tries to stay inside the lines.
 */
#include <Zumo32U4.h>

// --- Enums ---

// States. Here we just start out with a couple.
enum State {
  pause_state,
  run_state
};

// --- Constants

// What speed to run the motor
const int motorSpeed = 100;

// What value do we count as black?
const int blackColor = 700;

// --- Global Variables ---

Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3];
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

State state = pause_state;

// --- Setup Function
void setup() {
  // Initialize the line sensors, and turn on the LEDs for them.
  lineSensors.initThreeSensors();
  lineSensors.emittersOn();
}

// --- Main loop function
void loop() {
  // - Read in the values
  lineSensors.read(lineSensorValues);

  // Buttons
  bool buttonPress = buttonA.getSingleDebouncedPress();

  // - Change states
  if(buttonPress && state == pause_state) {
    state = run_state;
  }

  else if(buttonPress && state == run_state) {
    state = pause_state;
  }

  // - Set motor speeds
  if(state == run_state) {
    if(lineSensorValues[0] > blackColor && lineSensorValues[2] < blackColor) {
      // There's a line to the left. Veer right.
      motors.setSpeeds(motorSpeed, -motorSpeed);
    }
    else if(lineSensorValues[0] < blackColor && lineSensorValues[2] > blackColor) {
      // There's  line to the right. Veer left.
      motors.setSpeeds(-motorSpeed, motorSpeed);
    } else if(lineSensorValues[0] > blackColor && lineSensorValues[2] > blackColor) {
      // Ok, we are straight in on a line. Back up and spin.
      
      // This 'blocking' so it ignores button pushes, so it isn't possible to 'pause'
      // while doing this. You should code something better.
      motors.setSpeeds(-motorSpeed, -motorSpeed);
      delay(500);
      motors.setSpeeds(-motorSpeed, motorSpeed);
      delay(500);
    } else {
      // No lines. Go forward.
      motors.setSpeeds(motorSpeed, motorSpeed);
    }
  }
  else if(state == pause_state) {
    motors.setSpeeds(0, 0);
  }
  
  // Display the values.
  // Divide by 10 because our screen isn't large.

  // First value
  lcd.gotoXY(0, 0);
  lcd.print(lineSensorValues[0] / 10);
  lcd.print("  ");

  // Second value
  lcd.gotoXY(5, 0);
  lcd.print(lineSensorValues[1] / 10);
  lcd.print("  ");

  // Third value
  lcd.gotoXY(0, 1);
  lcd.print(lineSensorValues[2] / 10);
  lcd.print("  ");

  // State
  lcd.gotoXY(5, 1);
  lcd.print(state);
  lcd.print("  ");
  delay(2);
}
