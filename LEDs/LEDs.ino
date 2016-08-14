#include <Zumo32U4.h>

// Used to control the LCD display
// Documentation: http://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_l_c_d.html
// (Note that this inherits from Arduino's serial print class: https://www.arduino.cc/en/Serial/Print)
Zumo32U4LCD lcd;

// This is called when we are reprogrammed, when we have power-up, or when reset is hit
void setup() {
  // Clear the LCD screen
  lcd.clear();

  // Put "LED Example" on the display
  // Line 0
  lcd.gotoXY(0, 0);
  lcd.print("  LED");
  // Line 1
  lcd.gotoXY(0, 1);
  lcd.print("Example");
}

// This function is called over and over again
void loop() {
  // Turn on the red LED, and turn off the others
  // Documentation on these functions:
  // http://pololu.github.io/zumo-32u4-arduino-library/_zumo32_u4_8h.html
  // Source:
  // http://pololu.github.io/zumo-32u4-arduino-library/_zumo32_u4_8h_source.html
  ledRed(1);
  ledYellow(0);
  ledGreen(0);

  // Wait one second
  delay(1000);

  // Turn on the yellow LED, and turn off the others
  ledRed(0);
  ledYellow(1);
  ledGreen(0);

  // Wait one second
  delay(1000);

  // Turn on the green LED, and turn off the others
  ledRed(0);
  ledYellow(0);
  ledGreen(1);
  
  // Wait one second
  delay(1000);
}
