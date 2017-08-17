#define F_CPU 8000000

#include <avr/io.h>
#include <stdio.h>
#include "Input.h"
#include "Output.h"
#include <avr/interrupt.h>
#include <util/delay.h>

Input taster('D',3,true);
Output LED('C',0);

ISR(USART_RX_vect){
    uint8_t temp = UDR0;
    if(temp=='d'){
        UDR0 = taster.ison()+'0';
        LED.on();
    }
    _delay_ms(50);
}

int main(){

	UBRR0H = 0;
	UBRR0L = 51;							//9600 Baud
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);	// 8Bit Frame
	UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
    sei();

    while(true){
        if(taster.ison()){
            LED.on();
        }
        else{
            LED.off();
        }
        _delay_ms(50);
    }
    return 0;
}
