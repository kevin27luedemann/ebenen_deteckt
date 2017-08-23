/*
 * tm1367 library
 *
 * Created 23.08.2017 18:47
 * Author Kevin Luedemann
 */

#include "tm1637.h"

tm1637::tm1637(){
    digitToSegment[0 ] = 0b00111111;
    digitToSegment[1 ] = 0b00000110;
    digitToSegment[2 ] = 0b01011011;
    digitToSegment[3 ] = 0b01001111;
    digitToSegment[4 ] = 0b01100110;
    digitToSegment[5 ] = 0b01101101;
    digitToSegment[6 ] = 0b01111101;
    digitToSegment[7 ] = 0b00000111;
    digitToSegment[8 ] = 0b01111111;
    digitToSegment[9 ] = 0b01101111;
    digitToSegment[10] = 0b01110111;
    digitToSegment[11] = 0b01111100;
    digitToSegment[12] = 0b00111001;
    digitToSegment[13] = 0b01011110;
    digitToSegment[14] = 0b01111001;
    digitToSegment[15] = 0b01110001;
    segments[0] = 0;
    segments[1] = 0;
    segments[2] = 0;
    segments[3] = 0;
    setBrightness(7,true);
}

tm1637::~tm1637(){}

void tm1637::setBrightness(uint8_t m_brightness, bool on){
    brightness = m_brightness;
}

void tm1637::setSegments(){
    cli();
    i2c.twi_start();
    i2c.twi_write(TM1637_I2C_COMM1);
    i2c.twi_stop();

    i2c.twi_start();
    i2c.twi_write(TM1637_I2C_COMM2);
    for(uint8_t i=0; i<4; i++){
        if(segments[i] > 15){
            i2c.twi_write(digitToSegment[0]);
        }
        else{
            i2c.twi_write(digitToSegment[segments[i]]);
        }
    }
    i2c.twi_stop();

    i2c.twi_start();
    i2c.twi_write(TM1637_I2C_COMM3 | brightness | 0b00001000);
    i2c.twi_stop();
    sei();
}
