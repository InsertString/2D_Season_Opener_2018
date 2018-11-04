#include "main.h"
#include "flywheel.h"

int a = 0;
int new_rpm = 0;


//returns the value of the flywheel encoder//
int flywheelEncoder ()
{
  return encoderGet(flywheel_encoder);
}


//sets the power of the flywheel//
void setFlywheel (int power)
{
  motorSet(FLYWHEEL_Y, power);
  motorSet(FLYWHEEL_TOP, -power);
}


//sets the power of the indexer//
void setIndex (int power)
{
  motorSet(INDEX, power);
}


//calculates the flywheels RPM//
void CalculateflywheelRPM()
{
  if (new_rpm == 1)
  {
    //reset the flywheel encoder
    encoderReset(flywheel_encoder);
    startTimer(7);
    new_rpm = 0;
  }

  if (getTimer(7) > 500)
  {
    //set the rpm according to this formula
    //(encoder ticks / 500 milliseconds) * (1000 milliseconds / 1 second) * (60 seconds / 1 minute) * (gear ratio) / (360 encoder ticks / 1 rotation)
    RPM = abs(flywheelEncoder()) * 600 / 360;
    new_rpm = 1;
  }
  else
  {
    new_rpm = 0;
  }
}

int fly_error = 0;
int fly_int = 0;
int fly_past_error = 0;
int fly_der = 0;

void id_velocity(int target)
{
  fly_past_error = fly_error;
  fly_error = target - RPM;
  fly_der = fly_error - fly_past_error;
  if (fly_error > 100)
  {
    setFlywheel(fly_error * -0.06);
  }
  else if (fly_error <= 100)
  {
    fly_int += fly_error;
    //setFlywheel((fly_int * -0.0005));
  }
}

//code for flywheel control//
void flywheelControl ()
{
  //update the flywheel rpm
  CalculateflywheelRPM();


  //toggle for flywheel control
  if (joystickGetDigital(1, 6, JOY_UP))
  {
    for (; a <1; a++)
    {
      if (flyON == 1)
      {
        flyON = 0;
        flyTarget = 0;
      }
      else if (flyON == 0)
      {
        flyON = 1;
        flyTarget = HIGH_FLAG;
      }
    }
  }
  else if (!joystickGetDigital(1, 6, JOY_UP))
  {
    a = 0;
  }

  if (flyON == 1)
  {
    //id_velocity(HIGH_FLAG);
    setFlywheel(-127);
    /*
    the next few lines of code help control the flywheels velocity
    by appling full power until the rpm reaches or exceeds the
    target rpm then it reduces the power untill it is lower than
    the target and then repeats.
    */
    /*
    if (RPM < flyTarget)
    {
      setFlywheel(-127);
    }
    else if (RPM > flyTarget)
    {
      setFlywheel(-40);
    }*/














    /*
    the next set of if's and else if's are to control the intake system
    the system consists of an intake and an indexer. The indexer will
    always run backwards to cycle the balls in the intake to allow for
    further ball colection untill the driver presses the fire button
    after which the indexer will launch the balls into the flywheel.
    */
    if (joystickGetDigital(1, 5, JOY_UP))
    {
      motorSet(INTAKE_PE, -127);
      setIndex(-127);
    }
    else if (joystickGetDigital(1, 5, JOY_DOWN))
    {
      motorSet(INTAKE_PE, 127);
    }
    else if (joystickGetDigital(1, 6, JOY_DOWN))
    {
      motorSet(INTAKE_PE, -127);
      setIndex(127);
    }
    else
    {
      motorStop(INTAKE_PE);
      motorStop(INDEX);
    }
  }
  else if (flyON == 0)
  {
    setFlywheel(0);
    if (joystickGetDigital(1, 5, JOY_UP))
		{
			motorSet(INTAKE_PE, -127);
      setIndex(-127);
		}
		else if (joystickGetDigital(1, 5, JOY_DOWN))
		{
			motorSet(INTAKE_PE, 127);
		}
		else{
			motorStop(INTAKE_PE);
      motorStop(INDEX);
		}
  }
}
