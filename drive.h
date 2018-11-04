#ifndef _DRIVE_H_
#define _DRIVE_H_

#define TANK 1
#define ARCADE 2
#define FORWARD 1
#define BACKWARD -1

int joy_analog(int axis);

void setDrive(int left, int right);

void driveControl (int driveMode);

#endif
