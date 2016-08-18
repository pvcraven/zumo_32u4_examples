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

## Software setup

For help in getting a computer set up with the Zumo robot, see
[this video](https://youtu.be/L6iX8ZJ6nNo). You'll need:

* [Arduino Compiler](https://www.arduino.cc/en/Main/Software)
* [Driver support](https://www.pololu.com/docs/0J63/all#5.1) Install drivers and copy over the Pololu hardware folder
* From the Arduino compiler, go to Sketch...Include Library...Manage Libraries,
then search for "Zumo" and install the library.

## Easiest example:

* [LEDs](LEDs/LEDs.ino) - Learn to blink the three LEDs on the board. [Video](https://youtu.be/7KgZUn8ATDQ)

## Learn to use the sensors:

* [ProxSensorExample](ProxSensorExample/ProxSensorExample.ino) - Display the values for the proximity sensor on the LCD [Video](https://youtu.be/ddPo6HQvxzQ)
* [LineSensorExample](LineSensorExample/LineSensorExample.ino) - Display the values for the line sensors on the LCD
* [GyroSensorExample](GyroSensorExample/GyroSensorExample.ino) - Display robot angle on LCD [Video](https://youtu.be/XOp22Xx7ZnU)

## Move the robot:

* [MotorDeadReckoning](MotorDeadReckoning/MotorDeadReckoning.ino) - Move the robot using dead reckoning. (Timing.) [Video](https://youtu.be/k2DDa9nwVx0)
* [MotorEncoders](MotorEncoders/MotorEncoders.ino) - Move the robot using wheel encoders for more accurate distances.
* [TurnExample](TurnExample/TurnExample.ino) - Turn a certain number of degrees using the gyro
* [HeadingHold](HeadingHold/HeadingHold.ino) - More complex example. Attempts to hold-heading so we drive straight.

## Complex examples:

* [SumoExample](SumoExample/SumoExample.ino) - Very unintelligent Sumo robot.
* [MoveAndAvoid](MoveAndAvoid/MoveAndAvoid.ino) - Move the robot around, avoiding obstacles. [Video](https://youtu.be/mv8Kxi9K_sY)