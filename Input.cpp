/* 
* Input.cpp
*
* Created: 09.09.2015 16:01:30
* Author: kevin
*/


#include "Input.h"
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>

// default constructor
Input::Input(uint8_t Portpraefix, uint8_t Pinnumber, uint8_t pullup)
{
	Pin=Pinnumber;
	Port=Portpraefix;
	switch (Portpraefix)
	{
        /*
		case 'A':
			DDRA &= ~(1<<Pin);
            if(pullup){PORTA |= (1<<Pin);}
			break;*/
		case 'B':
			DDRB &= ~(1<<Pin);
            if(pullup){PORTB |= (1<<Pin);}
			break;
		case 'C':
			DDRC &= ~(1<<Pin);
            if(pullup){PORTC |= (1<<Pin);}
			break;
		case 'D':
			DDRD &= ~(1<<Pin);
            if(pullup){PORTD |= (1<<Pin);}
			break;
		default:
			break;
	}
} //Input

// default destructor
Input::~Input()
{
	switch (Port)
	{
        /*
		case 'A':
            PORTA &= ~(1<<Pin);
			break;*/
		case 'B':
            PORTB &= ~(1<<Pin);
			break;
		case 'C':
            PORTC &= ~(1<<Pin);
			break;
		case 'D':
            PORTD &= ~(1<<Pin);
			break;
		default:
			break;
	}
} //~Input


uint8_t Input::ison(){
	uint8_t returnparam=0;
	switch (Port)
	{
        /*
		case 'A':
			if (!(PINA&(1<<Pin)))
			{
				returnparam = 1;
			}
			break;*/
		case 'B':
			if (!(PINB&(1<<Pin)))
			{
                _delay_ms(1);
                if (!(PINB&(1<<Pin))){returnparam = 1;}
			}
			break;
		case 'C':
			if (!(PINC&(1<<Pin)))
			{
                _delay_ms(1);
                if (!(PINC&(1<<Pin))){returnparam = 1;}
			}
			break;
		case 'D':
			if (!(PIND&(1<<Pin)))
			{
                _delay_ms(1);
                if (!(PIND&(1<<Pin))){returnparam = 1;}
			}
			break;
	}
	return returnparam;
}

