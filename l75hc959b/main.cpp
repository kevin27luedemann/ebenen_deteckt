//this example runs with 2 shift registers

#define F_CPU 8000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "seven_seg.h"
#include "Input.h"
#include "Output.h"
#include "l74hc595b.h"

l74hc595b shift_reg(&DDRB,&PORTB,1,2,3,1);
seven_seg seg(4,&DDRC,&PORTC,0,&shift_reg);

ISR(TIMER0_OVF_vect){
    if(seg.ison){
        seg.next_segement();
    }
    TCNT0 = 100;
}

int main(void) {
    Input taster(&DDRD,&PORTD,&PIND,4,true);
    Output LED(&DDRB,&PORTB,0);

    //init timer fuer segment
    TIMSK |= (1<<TOIE0);
    TCCR0 |= (1<<CS02);// | (1<<CS00);
    sei();

    seg.on();
    uint16_t counter = 0;

	while(true) 
    {
        if(taster.pressed()){
            counter++;
            if(counter>1999){counter=0;}
            seg.set_number(0,counter/1000%10);
            seg.set_number(1,counter/100%10);
            seg.set_number(2,counter/10%10);
            seg.set_number(3,counter%10);
        }
        if(taster.ison()){LED.on();}
        else{LED.off();}
	}

}

