/* This example drives each motor on the Zumo forward, then
backward.  The yellow user LED is on when a motor should be
running forward and off when a motor should be running backward.
If a motor on your Zumo has been flipped, you can correct its
direction by uncommenting the call to flipLeftMotor() or
flipRightMotor() in the setup() function. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4LCD lcd;

unsigned int lineSensorValues[3];
void setup()
{
  // Wait for the user to press button A.
  buttonA.waitForButton();
  lineSensors.initThreeSensors();
  delay(1000);
}

void loop()
{
  int randDelay = random(150, 300);
  lcd.clear();
  lcd.print("Tot");
  lineSensors.read(lineSensorValues);
  
  motors.setLeftSpeed(400);
  motors.setRightSpeed(400);
 
  if (lineSensorValues[0] < 1000)
  {
    lcd.print("Line");
    motors.setLeftSpeed(-400);
    motors.setRightSpeed(-400);
    delay(randDelay);
    motors.setLeftSpeed(400);
    motors.setRightSpeed(-400);
    delay(randDelay);
 } 
 else if (lineSensorValues[2] < 1000)
  {
    lcd.print("Line");
    motors.setLeftSpeed(-400);
    motors.setRightSpeed(-400);
    delay(randDelay);
    motors.setLeftSpeed(-400);
    motors.setRightSpeed(400);
    delay(randDelay);
  }
  else{
    motors.setLeftSpeed(400);
    motors.setRightSpeed(400);
  }
}
