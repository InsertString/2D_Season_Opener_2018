#include "main.h"
#include "drive.h"

int b = 0;
int direction = FORWARD;




int joy_error = 0;//diference between the two joysticks for tank drive

int joy_analog(int axis)
{
  return joystickGetAnalog(1, axis);
}




//sets the power of the drive motors
void setDrive(int left, int right)
{
  motorSet(DRIVE_LEFT_Y, -left);
  motorSet(DRIVE_LEFT_MID_PE, -left);
  motorSet(DRIVE_RIGHT_Y, right);
  motorSet(DRIVE_RIGHT_MID_PE, right);
}

void driveControl (int driveMode)
{
  if (driveMode == TANK)
  {
    /*
    This next section of code helps the robot drive strate.
    One problem with tank drive is that there is a certain
    amount of human driving error that will cause the robot
    to drift away from the intended direction. The next few
    lines of code help reduce this accidental change in
    joystick values.
    */


    //this calculates the difference in joystick values
    joy_error = joy_analog(2) - joy_analog(3);

    //if the error is less then 8 and the absolute value of the joysticks are both greater than 50. . .
    if (abs(joy_error) < 8 && abs(joy_analog(2)) > 50 && abs(joy_analog(3)) > 50)
    {
      //if the error is positive and you are moving forward. . .
      if (joy_error > 0 && joy_analog(2) > 0 && joy_analog(3) > 0)
      {
        //then the right side is moving slower so we need it to equal the left side
        setDrive(joy_analog(2), joy_analog(2));
      }
      //if the error is negative and you are moving forward. . .
      else if (joy_error < 0 && joy_analog(2) > 0 && joy_analog(3) > 0)
      {
        //then the left side is moving slower so we need it to equal the right side
        setDrive(joy_analog(3), joy_analog(3));
      }
      //if the error is positive and you are moving backward. . .
      else if (joy_error > 0 && joy_analog(2) < 0 && joy_analog(3) < 0)
      {
        //then the left side is moving slower so we need it to equal the right side
        setDrive(joy_analog(3), joy_analog(3));
      }
      //if the error is negative and you are moving backwards. . .
      else if (joy_error < 0 && joy_analog(2) > 0 && joy_analog(3) > 0)
      {
        //then the right side is moving slower so we need it to equal the left side
        setDrive(joy_analog(2), joy_analog(2));
      }
      //otherwise. . .
      else
      {
        //drive normally
        setDrive(joy_analog(2), joy_analog(3));
      }
    }
    //otherwise
    else
    {
      //drive normally
      setDrive(joy_analog(2), joy_analog(3));
    }


  }
}
