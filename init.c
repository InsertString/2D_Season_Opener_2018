/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize()
{
  //~~~~~~~~~~~~~~~~~~~~~~~~FLYWHEEL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  RPM = 0;
  flyON = 0;
  flyTarget = 3000;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  //~~~~~~~~~~~~~~~~~~~~~~~~~LCD~~INIT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  lcdInit(uart2);
  lcdClear(uart2);
  lcdSetBacklight(uart2, false);
  last_lcd_btn_val = 0;
  curr_lcd_btn_val = 0;
  menu_state = 1;
  menu_level = 1;
  auton_complete = false;
  auton_number = 3;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  //~~~~~~~~~~~~~~~~~~~~~~~~SENSORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  flywheel_encoder = encoderInit(FLYWHEEL_ENCODER_TOP, FLYWHEEL_ENCODER_BOT, false);
  left_drive_encoder = encoderInit(LEFT_DRIVE_ENCODER_TOP, LEFT_DRIVE_ENCODER_BOT, false);
  right_drive_encoder = encoderInit(RIGHT_DRIVE_ENCODER_TOP, RIGHT_DRIVE_ENCODER_BOT, false);
  gyro_1 = gyroInit(GYRO, 0);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
}
