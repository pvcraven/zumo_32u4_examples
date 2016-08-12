#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ProximitySensors proxSensors;

void setup() {
  // put your setup code here, to run once:
  proxSensors.initThreeSensors();
}

void loop() {
  proxSensors.read();    
  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();
  lcd.gotoXY(0, 1);
  lcd.print(left_sensor);
  lcd.print(" ");
  lcd.print(center_left_sensor);
  lcd.print(" ");
  lcd.print(center_right_sensor);
  lcd.print(" ");
  lcd.print(right_sensor);
}
