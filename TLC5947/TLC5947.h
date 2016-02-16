#ifndef TLC5947_H
#define TLC5947_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>

class TLC5947
{
public:
	//Constructor
	TLC5947(uint8_t blank, uint8_t xlat);

	void send_data(uint16_t* column_data, uint8_t channels);

	uint8_t _xlat;
	uint8_t _blank;
};

#endif


