#include <SPI.h>

#include "TLC5947.h"
#include "LED_driver.h"

LED_driver LED_driver;

const uint8_t cursive_length = 38;
uint8_t cursive[cursive_length] = {62,65,129,254,1,125,134,125, 1,129,222,129,1,30,33,33, 17,1,13,18,37,25,2, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint8_t straight_length = 64;
uint8_t straight[straight_length] = {127,144,127,0,127,0,223,0,31,17,17,0,31,21,29,0, //Alice
                                    1,1,127,0,15,17,31,0,31,16,31,0,31,21,29,0,       //Jane
                                    127,1,7,1,127,0,14,17,14,0,14,17,14,0,15,9,127,   //Wood
                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0};                     //End space

uint8_t column_index = 0;
uint8_t color_index = 0;
                  
void setup()
{  
  LED_driver.brightness = 50;
  LED_driver.led_delay = 1000;
}

void loop()
{
  for(uint16_t j = 0; j < 4; j++)
  {
      LED_driver.set_matrix_shift(column_index, 1, straight, straight_length);
      LED_driver.send_pattern();
  }
  if(column_index == straight_length)
  {
    column_index = 0;
    if(color_index == 2)
    {
      color_index = 0;
    }
    else
    {
      color_index++;
    }
  }
  else
  {
    column_index++;
  }
}
