#include "main.h"
#include "timing.h"

int timer[10] = {0,0,0,0,0,0,0,0,0,0};

void startTimer(int timer_slot)
{
  timer[timer_slot] = millis();
}

void resetTimer(int timer_slot)
{
  timer[timer_slot] = millis();
}

int getTimer(int timer_slot)
{
  int i = millis() - timer[timer_slot];
  return i;
}
