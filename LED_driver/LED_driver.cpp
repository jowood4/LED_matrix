#include "LED_driver.h"

TLC5947 test(blank, xlat);

LED_driver::LED_driver(void)
{
	DDRD = 0xFF;  //sets pins 0-7 as outputs
}

void LED_driver::set_zero(void)
{
	for(uint8_t i=0; i<channels; i++)
	{
		column_data[i] = 0;
	}
	test.send_data(column_data, channels);
}

void LED_driver::set_color_fix(uint8_t column, uint8_t red, uint8_t green, uint8_t blue)
{
	column_data[fix_column((column*3)+0)] = red;
	column_data[fix_column((column*3)+1)] = green;
	column_data[fix_column((column*3)+2)] = blue;
}

void LED_driver::set_color(uint8_t column, uint8_t red, uint8_t green, uint8_t blue)
{
	column_data[(column*3)+0] = red;
	column_data[(column*3)+1] = green;
	column_data[(column*3)+2] = blue;
}

//This function sets the color buffers from the user data
void LED_driver::set_matrix_shift(uint8_t shift, uint8_t color, uint8_t data[], uint8_t data_length)
{
	uint8_t temp_buffer[columns];
	
	for(uint8_t j = 0; j < columns; j++)
	{
		temp_buffer[j] = 0;
	}
	
	if(shift <= columns)
	{
		for(uint8_t j = 0; j < shift; j++)
		{
			temp_buffer[columns-shift+j] = data[j];	
		}	
	}
	else if(shift > data_length)
	{
		for(uint8_t j = 0; j < columns; j++) // - (shift - data_length); j++)
		{
			temp_buffer[j] = data[j+(shift-columns)];
		}
	}
	else
	{
		for(uint8_t j = 0; j < columns; j++)
		{
			temp_buffer[j] = data[j+(shift-columns)];
		}
	}

	set_matrix(color, temp_buffer);
}

//This function sets the color buffers from the user data
void LED_driver::set_matrix(uint8_t color, uint8_t data[columns])
{
	for(uint8_t j = 0; j < columns; j++)
	{
		color_buffer[color][j] = data[j]; //brightness * 
	}			
}

//This function sends out column data and cycles through rows
void LED_driver::send_pattern(void)
{
	for(uint8_t i=0; i<8; i++)
	{	
		for(uint8_t j=0; j<channels; j++)
		{	
			column_data[j] = 0;
		}

		for(uint8_t j=0; j<columns; j++)
		{
			set_color_fix(j, bitRead(color_buffer[0][j],7-i) * brightness,
							 bitRead(color_buffer[1][j],7-i) * brightness,
							 bitRead(color_buffer[2][j],7-i) * brightness);
		}

		test.send_data(column_data, channels);

		PORTD = (0x01 << i);		
		delayMicroseconds(led_delay);
		PORTD = 0x00;
		delayMicroseconds(led_delay);
	}
}

//This function is only used for the special TLC5947 wiring
uint8_t LED_driver::fix_column(uint8_t old_col)
{
	uint8_t fix_col[48];
	fix_col[8 * 3 + 1] = 0;
	fix_col[8 * 3 + 0] = 1;
	fix_col[9 * 3 + 2] = 2;
	fix_col[10 * 3 + 1] = 3;
	fix_col[10 * 3 + 0] = 4;
	fix_col[11 * 3 + 2] = 5;
	fix_col[12 * 3 + 2] = 6;
	fix_col[12 * 3 + 0] = 7;
	fix_col[13 * 3 + 1] = 8;
	fix_col[14 * 3 + 2] = 9;
	fix_col[14 * 3 + 0] = 10;
	fix_col[15 * 3 + 1] = 11;
	fix_col[7 * 3 + 1] = 12;
	fix_col[6 * 3 + 0] = 13;
	fix_col[6 * 3 + 2] = 14;
	fix_col[5 * 3 + 1] = 15;
	fix_col[4 * 3 + 0] = 16;
	fix_col[4 * 3 + 2] = 17;
	fix_col[3 * 3 + 2] = 18;
	fix_col[2 * 3 + 0] = 19;
	fix_col[2 * 3 + 1] = 20;
	fix_col[1 * 3 + 2] = 21;
	fix_col[0 * 3 + 0] = 22;
	fix_col[0 * 3 + 1] = 23;
	fix_col[0 * 3 + 2] = 24;
	fix_col[1 * 3 + 1] = 25;
	fix_col[1 * 3 + 0] = 26;
	fix_col[2 * 3 + 2] = 27;
	fix_col[3 * 3 + 1] = 28;
	fix_col[3 * 3 + 0] = 29;
	fix_col[4 * 3 + 1] = 30;
	fix_col[5 * 3 + 2] = 31;
	fix_col[5 * 3 + 0] = 32;
	fix_col[6 * 3 + 1] = 33;
	fix_col[7 * 3 + 2] = 34;
	fix_col[7 * 3 + 0] = 35;
	fix_col[15 * 3 + 0] = 36;
	fix_col[15 * 3 + 2] = 37;
	fix_col[14 * 3 + 1] = 38;
	fix_col[13 * 3 + 0] = 39;
	fix_col[13 * 3 + 2] = 40;
	fix_col[12 * 3 + 1] = 41;
	fix_col[11 * 3 + 0] = 42;
	fix_col[11 * 3 + 1] = 43;
	fix_col[10 * 3 + 2] = 44;
	fix_col[9 * 3 + 0] = 45;
	fix_col[9 * 3 + 1] = 46;
	fix_col[8 * 3 + 2] = 47;
	return fix_col[old_col];
}

