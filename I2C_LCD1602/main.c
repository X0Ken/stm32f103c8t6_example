#include "stm32f10x.h"
#include "delay.h"
#include "I2C.h"
#include "LiquidCrystal_I2C.h"


int main()
{
  LCDI2C_init(0x3F,16,2);
  LCDI2C_backlight();
  LCDI2C_write_String("Hello Habrahabr");
  LCDI2C_setCursor(0, 1);
  LCDI2C_write_String("Hello Github");
  while(1);
}
