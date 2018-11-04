#include "main.h"
#include "auton_funcs.h"


driveFuncVariable driveFunc;
driveFuncVariable turnFunc;
int out_L;
int out_R;

//returns the current value of the left encoder
int LeftDriveEnc()
{
  return encoderGet(left_drive_encoder);
}

//returns the value of the right encoder
int RightDriveEnc()
{
  return encoderGet(right_drive_encoder);
}

//returns the current average value of both drive encoders
int averageDriveEnc()
{
  return ((LeftDriveEnc() + RightDriveEnc()) / 2);
}





int drive_func_step = 0;
int drive_return_status = INCOMPLETE;
/*~~~~~~~~~~~~~~~~~~~~~~~DRIVE~~~~~~~~~~~~~~~~~~~~~~//

The drive function uses a step system to ensure that
certain parts of the function so not run again.

The function is an integer function so that it can
return weather or not the function has finished.

There is a 3 second timeout so that in case the robots
movement gets interupted, it will automatically exit
the function.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int drive(int target)
{
  if (drive_func_step == 0)
  {
    //reset sensor values
    encoderReset(left_drive_encoder);
    encoderReset(right_drive_encoder);
    gyroReset(gyro_1);
    //update the step
    drive_func_step = 1;
    //reset the drive function variables
    driveFunc.error = target;
    driveFunc.past_error = 0;
    driveFunc.integral = 0;
    driveFunc.derivative = 0;
    driveFunc.integral_threshold = 50;
    driveFunc.gyro_target = gyroVal();
    driveFunc.gyro_error = 0;
    //start the timer using slot 0
    startTimer(0);
    //start the debug stream
    printf("START OF DRIVE FUNCTION\n");
    printf("Target = %d\n", target);
    printf("Error = \n");
    drive_return_status = INCOMPLETE;
    //output incomplete for the autonomous task
  }
  else if (drive_func_step == 1 && getTimer(0) < 3000)
  {
    //update debug stream
    printf("%d\n",driveFunc.error);
    //calculate past error first because it uses the same variable from the last cycle
    driveFunc.past_error = driveFunc.error;
    //calculate the error
    driveFunc.error = target - LeftDriveEnc();
    driveFunc.gyro_error = driveFunc.gyro_target - gyroVal();
    //calculate the integral
    if (driveFunc.error > driveFunc.integral_threshold)
      driveFunc.integral += driveFunc.error;
    else
      driveFunc.integral = 0;
    //calculate derivative
    driveFunc.derivative = driveFunc.error - driveFunc.past_error;

    //out_R = ((driveFunc.error * 0.5) + (driveFunc.integral * 0.01) + (driveFunc.derivative * 5));
    //out_L = ((driveFunc.error * 0.5) + (driveFunc.integral * 0.01) + (driveFunc.derivative * 5));
    out_R = (driveFunc.error * 0.5) + driveFunc.gyro_error * 12;
    out_L = (driveFunc.error * 0.5) - driveFunc.gyro_error * 12;

    setDrive(out_L, out_R);

    if (abs(driveFunc.error) < 5)
    {
      drive_func_step = 2;
      resetTimer(0);
    }
    drive_return_status = INCOMPLETE;
  }
  else if (drive_func_step == 2 || getTimer(0) > 3000)
  {
    if (target > 0)
      setDrive(-5 + driveFunc.gyro_error * 1, -5 - driveFunc.gyro_error * 1);
    else if (target < 0)
      setDrive(5 + driveFunc.gyro_error * 1, 5 - driveFunc.gyro_error * 1);
    if (getTimer(0) > 100)
    {
      setDrive(0, 0);
      //finish the debug stream
      printf("END OF DRIVE FUNCTION");
      drive_return_status = COMPLETE;
    }
  }
  return drive_return_status;
}

int launchball_step = 0;
int launchball_return_status = INCOMPLETE;
int launch_timer_started = 0;
/*
This function revs up the flywheel to a target rpm
then launches a ball.

The ball will be launched as soon as the flywheel
reaches the target velocity then it will wait for
about 500ms for the ball to actually be launched
before it returns COMPLETE and turns the flywheel
off.
*/
int LaunchBall(int targetRPM)
{
  if (launchball_step == 0)
  {
    setIndex(-127);
    motorSet(INTAKE_PE, -127);
    launchball_step = 1;
    launchball_return_status = INCOMPLETE;
  }
  else if (launchball_step == 1)
  {
    if (RPM < targetRPM)
    {
      setFlywheel(-127);
    }
    else
    {
      setFlywheel(-60);
    }

    if (RPM > targetRPM)
    {
      setIndex(127);
      if (launch_timer_started == 0)
      {
        startTimer(1);
        launch_timer_started = 1;
      }

      if (getTimer(1) > 250)
      {
        launchball_step = 2;
      }
    }

    launchball_return_status = INCOMPLETE;
  }
  else if (launchball_step == 2)
  {
    setFlywheel(0);
    setIndex(0);
    motorStop(INTAKE_PE);
    launch_timer_started = 0;
    launchball_return_status = COMPLETE;
  }
  return launchball_return_status;
}

int gyroTurn_step = 0;
int gyroTurn_return_state = INCOMPLETE;

int gyroVal()
{
  return gyroGet(gyro_1);
}

int gyroTurn(int target)
{
  switch (gyroTurn_step)
  {
    case 0 :
    //reset the turn function variables
    turnFunc.error = target;
    turnFunc.past_error = 0;
    turnFunc.derivative = 0;
    turnFunc.integral = 0;
    turnFunc.integral_threshold = 12;
    gyroTurn_step++;
    gyroTurn_return_state = INCOMPLETE;
    startTimer(6);
    printf("start of turn\n");
    break;
    case 1 :
    //set turn function variables
    turnFunc.past_error = turnFunc.error;
    turnFunc.error = target - gyroVal();
    //calculate derivative
    turnFunc.derivative = turnFunc.error - turnFunc.past_error;
    //calculate integral
    if (turnFunc.error < turnFunc.integral_threshold)
      turnFunc.integral += turnFunc.error;
    else
      turnFunc.integral = 0;

    out_R = (turnFunc.error * 1.2) + (turnFunc.integral * 0.0002);
    out_L = (turnFunc.error * -1.2) + (turnFunc.integral * -0.0002);
    //power the drive
    setDrive(out_L, out_R);
    //if the robot is less than 5 degrees off from the target. . .
    if (abs(turnFunc.error) < 4 || getTimer(6) > 1000)
    {
      //exit the step
      if (getTimer(3) > 100 || getTimer(6) > 1000)
        gyroTurn_step++;
    }
    else
    {
      startTimer(3);
    }
    gyroTurn_return_state = INCOMPLETE;
    printf("%d\n",turnFunc.error);
    break;
    case 2 :
    setDrive(0, 0);
    gyroTurn_return_state = COMPLETE;
    printf("end of turn func");
    break;
  }
  return gyroTurn_return_state;
}
