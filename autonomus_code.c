#include "main.h"
#include "autonomus_code.h"

int auto_step = 0;
int i;




void FlagAuton(int colour)
{
  switch (auto_step)
  {
    case 0 :
    drive_func_step = 0;
    launchball_step = 0;
    auto_step = 1;
    printf("completed step 0");
    break;
    case 1 :
    i = drive(-1040);
    if (i == COMPLETE)
    {
      auto_step = 2;
      drive_func_step = 0;
      printf("completed step 1");
      startTimer(5);
    }
    break;
    case 2 :
    i = drive(-200);
    armHold_func(1000);
    if (i == INCOMPLETE)
    {
      setIndex(-127);
      motorSet(INTAKE_PE, -127);
      startTimer(4);
    }
    if (i == COMPLETE && getTimer(4) > 100)
    {
      auto_step = 3;
      drive_func_step = 0;
    }
    break;
    case 3 :
    armHold_func(1000);
    if (LeftDriveEnc() > 700)
    {
      setFlywheel(-127);
    }

    i = drive(1160);
    if (i == COMPLETE)
    {
      auto_step = 4;
      drive_func_step = 0;
    }
    break;
    case 4 :
    armHold_func(1000);
    if (colour == RED)
      i = gyroTurn(91);
    else if (colour == BLUE)
      i = gyroTurn(-75);
    if (i == COMPLETE)
    {
      drive_func_step = 0;
      auto_step = 5;
      setFlywheel(-127);
    }
    break;
    case 5 :
    armHold_func(1000);
    if (RPM > 2900)
    {
      auto_step = 6;
      encoderReset(left_drive_encoder);
      startTimer(6);
    }
    break;
    case 6 :
    setIndex(127);
    if (getTimer(6) > 100)
    {
      auto_step = 7;
    }
    break;
    case 7 :
    i = drive(1100);
    if (i == COMPLETE)
    {
      setFlywheel(0);
      auto_step = 8;
      drive_func_step = 0;
    }
    break;
    case 8 :
    armHold_func(200);
    i = drive(-230);
    if (i == COMPLETE)
    {
      drive_func_step = 0;
      auto_step = 9;
      gyroTurn_step = 0;
    }
    break;
    case 9 :
    if (colour == RED)
      i = gyroTurn(90);
    else if (colour == BLUE)
     i = gyroTurn(-65);
    if (i == COMPLETE)
    {
      auto_step = 10;
      drive_func_step = 0;
      gyroTurn_step = 0;
    }
    break;
    case 10 :
    i = drive(200);
    if (i == COMPLETE)
    {
      auto_step = 11;
      drive_func_step = 0;
      gyroTurn_step = 0;
    }
    break;
    case 11 :
    armHold_func(1000);
    break;
    /*
    case 6 :
    if (LeftDriveEnc() < 150)
    {
      setDrive(30, 30);
      startTimer(7);
    }
    else
    {
      setDrive(0, 0);
      setIndex(127);
      motorSet(INTAKE_PE,-127);
      if (getTimer(7) > 500)
      {
        setDrive(90, 91);
        auto_step = 7;
        startTimer(7);
      }
    }
    break;
    case 7 :
    if (LeftDriveEnc() > 900)
    {
      if (getTimer(7) > 500)
      {
        auto_step = 8;
        drive_func_step = 0;
      }
      setDrive(0, 0);
      setFlywheel(0);
    }
    break;
    case 8 :
    armHold_func(150);
    i = drive(-200);
    if (i == COMPLETE)
    {
      auto_step = 9;
      drive_func_step = 0;
      gyroTurn_step = 0;
    }
    break;
    case 9 :
    if (colour == RED)
      i = gyroTurn(90);
    else if (colour == BLUE)
      i = gyroTurn(-80);
    if (i == COMPLETE)
    {
      auto_step = 10;
    }
    break;
    case 10 :
    i = drive(300);
    if (i == COMPLETE)
    {
      auto_step = 11;
    }
    break;
    case 11 :
    armHold_func(900);
    break;
    */
  }
}













void ParkAuton(int colour)
{
  switch(auto_step)
  {
    case 0 :
    drive_func_step = 0;
    gyroTurn_step = 0;
    launchball_step = 0;
    auto_step++;
    break;
    case 1 :
    i = drive(-800);
    if (i == COMPLETE)
    {
      auto_step++;
      drive_func_step = 0;
      startTimer(5);
    }
    break;
    case 2 :
    i = drive(-350);
    if (i == INCOMPLETE)
    {
      setIndex(-127);
      motorSet(INTAKE_PE, -127);
    }
    if (i == COMPLETE)
    {
      auto_step++;
      drive_func_step = 0;
    }
    break;
    case 3 :
    i = drive(100);
    if (i == INCOMPLETE)
    {
      setIndex(-127);
      motorSet(INTAKE_PE, -127);
    }
    if (i == COMPLETE)
    {
      auto_step++;
      drive_func_step = 0;
    }
    break;
    case 4 :
    if (colour == RED)
      i = gyroTurn(-90);
    else if (colour == BLUE)
      i = gyroTurn(90);
    if (i == COMPLETE)
    {
      setIndex(0);
      motorSet(INTAKE_PE, 0);
      auto_step++;
      gyroTurn_step = 0;
    }
    break;
    case 5 :
    i = drive(320);
    if (i == COMPLETE)
    {
      drive_func_step = 0;
      auto_step++;
    }
    break;
    case 6 :
    armHold_func(1000);
    if (colour == RED)
      i = gyroTurn(-10);
    else if (colour == BLUE)
      i = gyroTurn(10);
    if (analogRead(ARM_POT) > 500 && i == COMPLETE)
    {
      auto_step++;
    }
    break;
    case 7 :
    armHold_func(400);
    i = drive(-1720);
    if (i == COMPLETE)
    {
      auto_step++;
    }
    break;
  }
}










































void RedParkAuton ()
{

}








void AutoTest()
{
  switch (auto_step)
  {
    case 0 :
    i = gyroTurn(-90);
    if (i == COMPLETE)
    {
      auto_step++;
    }
    break;
    case 1 :
    break;
  }
}
