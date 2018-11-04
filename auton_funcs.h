#ifndef _AUTON_FUNCS_H_
#define _AUTON_FUNCS_H_

#define COMPLETE 10
#define INCOMPLETE 5

int LeftDriveEnc();
int RightDriveEnc();
int averageDriveEnc();

int drive_func_step;
int launchball_step;

struct driveFuncVariable
{
  int error;
  int past_error;
  int integral;
  int integral_threshold;
  int derivative;
  int gyro_error;
  int gyro_target;
};
typedef struct driveFuncVariable driveFuncVariable;

int gyroTurn_step;
int gyroTurn_return_state;
int gyroVal();
int gyroTurn(int target);

int drive_return_status;
int drive(int target);

int LaunchBall(int targetRPM);

#endif
