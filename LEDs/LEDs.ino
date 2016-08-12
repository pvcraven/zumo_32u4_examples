#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;

void setup() {
  lcd.clear();
}

void loop() {
  ledRed(1);
  ledYellow(0);
  ledGreen(0);
  delay(1000);

  ledRed(0);
  ledYellow(1);
  ledGreen(0);
  delay(1000);
  
  ledRed(0);
  ledYellow(0);
  ledGreen(1);
  delay(1000);
  
}
