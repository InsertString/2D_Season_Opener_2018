#ifndef _LCD_H_
#define _LCD_H_

#define YES 1
#define NO 2
#define LCD_FLYWHEEL 1
#define LCD_GYRO 2
#define LCD_ARM_POT 3

int last_lcd_btn_val;
int curr_lcd_btn_val;
int auton_complete;
int auton_number;

int LCD_btn();

int LCD_left_pressed();

int LCD_right_pressed();

int LCD_center_pressed();

int menu_state;
int menu_level;

void LCD_driver_control();

void auton_selection();

void lcd_code ();

#endif
