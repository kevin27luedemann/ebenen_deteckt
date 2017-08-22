//this example runs with 2 shift registers

#define F_CPU 8000000
#define BAUD 9600

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "seven_seg.h"
#include "Input.h"
#include "Output.h"
#include "l74hc595b.h"
#include "com.h"

l74hc595b shift_reg(&DDRB,&PORTB,1,2,3,1);
seven_seg seg(4,&DDRC,&PORTC,0,&shift_reg);
Input taster(&DDRD,&PORTD,&PIND,6,true);
Output LED(&DDRB,&PORTB,0);

ISR(TIMER0_OVF_vect){
    if(seg.ison){
        seg.next_segement();
    }
    TCNT0 = 100;
}

ISR(USART_RXC_vect){
    uint8_t temp = uart_getc();
    static uint8_t count = 0;
    if(temp=='d'){
        uart_putc(taster.ison()+'0');
    }
    else{
        if(count==4){
            seg.dot_pos = temp - '0';
            count = 0;
        }
        else{
            seg.set_number(count,temp-'0');
            if(count==0){
                count++;
            }
            else if(count==1){
                count++;
            }
            else if(count==2){
                count++;
            }
            else if(count==3){
                count++;
            }
        }
    }
}

int main(void) {

    //USART setting
	//UBRRH = 0;
	//UBRRL = 51;							//9600 Baud
	//UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);	// 8Bit Frame
	//UCSRB = (1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
    uart_init();

    //init timer fuer segment
    TIMSK |= (1<<TOIE0);
    TCCR0 |= (1<<CS02);// | (1<<CS00);
    sei();

    seg.on();
    seg.dot_pos = 1;
    seg.set_number(0,0);
    seg.set_number(1,0);
    seg.set_number(2,0);
    seg.set_number(3,0);

    uint16_t counter = 0;
	while(true) 
    {
        if(taster.pressed()){
            counter++;
            if(counter>1999){counter=0;}
            //seg.set_number(0,counter/1000%10);
            //seg.set_number(1,counter/100%10);
            //seg.set_number(2,counter/10%10);
            //seg.set_number(3,counter%10);
        }
        if(taster.ison()){LED.on();}
        else{LED.off();}
	}

}

