#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "Arduino.h"
#include "SPI.h"
#include "TLC5947.h"

const uint8_t blank = 8;
const uint8_t xlat = 9;

const uint8_t row[] = {0, 1, 2, 3, 4, 5, 6, 7};

const uint8_t matrices = 2;
const uint8_t columns = matrices * 8;
const uint8_t channels = columns * 3;

class LED_driver
{
public:
    //Constructor
    LED_driver();

    //Set new column_data and then sends it
    void set_color(uint8_t column, uint8_t red, uint8_t green, uint8_t blue);
    void set_color_fix(uint8_t column, uint8_t red, uint8_t green, uint8_t blue);

    //Sends zeros to all column channels
    void set_zero(void);

    uint8_t fix_column(uint8_t old_col);

    void send_pattern(void);
    //void set_matrix(uint8_t color, uint8_t data[8][columns]);
	//void set_matrix_shift(uint8_t shift, uint8_t color, uint8_t data[][8], uint8_t data_length);
	
	void set_matrix(uint8_t color, uint8_t data[columns]);
	void set_matrix_shift(uint8_t shift, uint8_t color, uint8_t data[], uint8_t data_length);

    //These properties store data for the matrix
    uint16_t column_data[channels];
    
    uint16_t led_delay;
	uint8_t brightness;
	
	uint8_t color_buffer[3][columns]; //0 = red, 1 = blue, 2 = green.  Stores current display
	//uint8_t color_buffer[3][8][columns]; //0 = red, 1 = blue, 2 = green.  Stores current display
    //uint8_t red_buffer[8][columns];
    //uint8_t blue_buffer[8][columns];
    //uint8_t green_buffer[8][columns];
};

#endif
