// Line Sensor Example
#include <Zumo32U4.h>

// LCD Screen
Zumo32U4LCD lcd;

// Line sensors. Documentation:
// http://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html
Zumo32U4LineSensors lineSensors;

// Sensor values will go in this array
unsigned int lineSensorValues[3];

void setup() {
  // Initialize the sensors, and turn on the LEDs for them.
  lineSensors.initThreeSensors();
  lineSensors.emittersOn();
}

void loop() {
  // Read in the values
  lineSensors.read(lineSensorValues);

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

  delay(250);
}
