#include "main.h"
#include "arm.h"

int armHold;
int armTarget = 205;
int armError = 0;

float ArmAngle()
{
  float a;
  a = (analogRead(ARM_POT) - 1000) * 250 / 4095;
  return a;
}

int ArmArcLength()
{
  int a;
  a = 2 * 3.1415 * 52 * ArmAngle() / 360;
  return a;
}

int ArmHeight()
{
  int a;
  a = 52 * sin(ArmAngle());
  return a;
}

void setArm(int power)
{
  motorSet(ARM_PE, power);
}


void armHold_func(int target)
{
  int error = target - analogRead(ARM_POT);
  setArm((error * 0.15) + 5);
}




int past_target = 0;

void armControl()
{
  //code for arm presets
  /*
  the arm will aplly power until it reaches the target
  pot value at which point it will stop and apply holding
  power in order too maintain its position
  */

  if (joystickGetDigital(1, 7, JOY_DOWN))
  {
    armTarget = 200;
    past_target = armTarget;
  }
  else if (joystickGetDigital(1, 7, JOY_RIGHT))
  {
    armTarget = 975;
    past_target = armTarget;
  }
  else if (joystickGetDigital(1, 7, JOY_UP))
  {
    armTarget = 2000;
  }
  else if (!joystickGetDigital(1, 7, JOY_UP))
  {
    armTarget = past_target;
  }

  armError = armTarget - analogRead(ARM_POT);

  if (armTarget == 200)
    motorSet(ARM_PE, armError * 0.15);
  else
  {
    motorSet(ARM_PE, (armError * 0.2));
  }
}
