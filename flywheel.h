#ifndef _FLYWHEEL_H_
#define _FLYWHEEL_H_

int RPM;
int flyON;
int flyTarget;
int new_rpm;





#define HIGH_FLAG 3200

int flywheelEncoder ();

void setFlywheel(int power); // sets the motor power for the flywheel

void CalculateflywheelRPM(); // calculates the rpm of the flywheel and returns the value

void flywheelControl ();

int velocityPI();

void setIndex(int power);

#endif
