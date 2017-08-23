/*
 * tm1367 library
 *
 * Created 23.08.2017 18:47
 * Author Kevin Luedemann
 */

#ifndef __TM1637_H__
#define __TM1637_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.h"

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

class tm1637
{
private:
	I2C i2c;
	uint8_t brightness;
	uint8_t digitToSegment[16];


public:
	tm1637();
	~tm1637();

	uint8_t segments[4];

	void setBrightness(uint8_t m_brightness, bool on);
	void setSegments();

};

#endif
