# Example code for Polulu's Arduino-based Zumo 32U4 robot

*Examples by Prof. Craven*

This is a repository of example code
for [Pololu's Zumo 32U4 robot](https://www.pololu.com/category/170/zumo-32u4-robot).
Their [user guide is here](https://www.pololu.com/docs/0J63). To get
started with their robot, download the
[Arduino compiler](https://www.arduino.cc/en/Main/Software),
Next install the
[A-Star support for the Arduino compiler](https://github.com/pololu/a-star).
(Look down a ways on that page for where to copy things over to install.)
Finally, [install the Zumo library](https://www.pololu.com/docs/0J63/6).

## Easiest example:

* [LEDs](LEDs/LEDs.ino) - Learn to blink the three LEDs on the board

## Learn to use the sensors:

* [ProxSensorExample](ProxSensorExample/ProxSensorExample.ino) - Display the values for the proximity sensor on the LCD
* [LineSensorExample](LineSensorExample/LineSensorExample.ino) - Display the values for the line sensors on the LCD
* [GyroSensorExample](GyroSensorExample/GyroSensorExample.ino) - Display robot angle on LCD

## Move the robot:

* [MotorDeadReckoning](MotorDeadReckoning/MotorDeadReckoning.ino) - Move the robot using dead reckoning. (Timing.)
* [MotorEncoders](MotorEncoders/MotorEncoders.ino) - Move the robot using wheel encoders for more accurate distances.
* [TurnExample](TurnExample/TurnExample.ino) - Turn a certain number of degrees using the gyro
* [HeadingHold](HeadingHold/HeadingHold.ino) - More complex example. Attempts to hold-heading so we drive straight.