#include "main.h"
#include "lcd.h"



//~~~~~~~~~~~~~~~~~~~~~~~LCD~BUTTONS~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//function that returns which lcd button is pressed//
int LCD_btn()
{
  return lcdReadButtons(uart2);
}

//function that returns 1 when the left LCD button is pressed//
int LCD_left_pressed()
{
  if (LCD_btn() == LCD_BTN_LEFT && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//function that returns 1 when the right LCD button is pressed//
int LCD_right_pressed()
{
  if (LCD_btn() == LCD_BTN_RIGHT && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//function that returns 1 when the center LCD button is pressed//
int LCD_center_pressed()
{
  if (LCD_btn() == LCD_BTN_CENTER && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//





//~~~~~~~~~~~~~~~~~~~~~LCD~MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void LCD_driver_control()
{
  lcdPrint(uart2, 1, "M: %1.2f, PE: %1.2f", (double)powerLevelMain()/1000, (double)analogRead(2)/275);

  if (menu_state == LCD_FLYWHEEL)
  {
    if (new_rpm == 1)
      lcdPrint(uart2, 2, "RPM : %4d", RPM);
  }
  else if (menu_state == LCD_GYRO)
  {
    lcdPrint(uart2, 2, "GYRO : %3d", gyroGet(gyro_1));
  }
  else if (menu_state == LCD_ARM_POT)
  {
    lcdPrint(uart2, 2, "ARM POT : %4d", analogRead(ARM_POT));
  }

  if (LCD_left_pressed())
  {
    if (menu_state == LCD_FLYWHEEL)
      menu_state = LCD_ARM_POT;
    else
      menu_state--;
  }
  else if (LCD_right_pressed())
  {
    if (menu_state == LCD_ARM_POT)
      menu_state = LCD_FLYWHEEL;
    else
      menu_state++;
  }
}

void auton_selection()
{
  lcdPrint(uart2, 1, "M: %1.2f, PE: %1.2f", (double)powerLevelMain()/1000, (double)analogRead(2)/275);

  switch(auton_number)
  {
    case 1 :
  //lcdPrint(uart2, 2, "<<              >>");
    lcdPrint(uart2, 2, "<<  RED FLAG  >>");
    break;
    case 2 :
    lcdPrint(uart2, 2, "<<  RED PARK  >>");
    break;
    case 3 :
    lcdPrint(uart2, 2, "<< BLUE  FLAG >>");
    break;
    case 4 :
    lcdPrint(uart2, 2, "<< BLUE  PARK >>");
    break;
    case 5 :
    lcdPrint(uart2, 2, "AutoTest");
    break;
  }

  if (LCD_left_pressed())
  {
    if (auton_number == 1)
      auton_number = 5;
    else
      auton_number--;
  }
  else if (LCD_right_pressed())
  {
    if (auton_number == 5)
      auton_number = 1;
    else
      auton_number++;
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void lcd_code ()
{
  last_lcd_btn_val = curr_lcd_btn_val;
  curr_lcd_btn_val = lcdReadButtons(uart2);

  if (LCD_center_pressed())
    auton_complete = true;

  if (auton_complete == false)
  {
    auton_selection();
  }
  else if (auton_complete == true)
  {
    LCD_driver_control();
  }
  delay(10);
}
