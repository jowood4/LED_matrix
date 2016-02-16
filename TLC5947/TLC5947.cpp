#include "TLC5947.h"

TLC5947::TLC5947(uint8_t blank, uint8_t xlat)
{
	_blank = blank;
	_xlat = xlat;

	pinMode(_blank, OUTPUT);
	pinMode(_xlat, OUTPUT);

	digitalWrite(_blank, 0);
	digitalWrite(_xlat, 0);

	SPI.begin();
}

void TLC5947::send_data(uint16_t* column_data, uint8_t channels)
{
	digitalWrite(_xlat,0);
        for(uint8_t i=0; i<channels-1; i=i+2)
	{
		SPI.transfer(column_data[channels-1-i] >> 4);
		SPI.transfer(((column_data[channels-1-i] & 0x000F) << 4) + ((column_data[channels-2-i] & 0x0F00) >> 8));
		SPI.transfer(column_data[channels-2-i] & 0x00FF);
	}

        digitalWrite(_xlat,1);
	//delay(1);
        digitalWrite(_xlat,0);
}
