#define F_CPU 8000000

#include <avr/io.h>
#include <stdio.h>
#include "Input.h"
#include "Output.h"
#include <avr/interrupt.h>
#include <util/delay.h>

Input taster('D',3,true);
Input deadend_up('D',2,true);
Input deadend_do('D',4,true);
Output LED('C',0);

void send_UART(char data){
    while(!(UCSRA&(1<<UDRE)));
    UDR = data;
}

ISR(USART_RXC_vect){
    uint8_t temp = UDR;
    if(temp=='d'){
        send_UART(taster.ison()+'0');
        send_UART(deadend_up.ison()+'0');
        send_UART(deadend_do.ison()+'0');
        LED.on();
    }
}

int main(){

	UBRRH = 0;
	UBRRL = 51;							//9600 Baud
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);	// 8Bit Frame
	UCSRB = (1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
    sei();

    while(true){
        if(taster.ison()){
            LED.on();
        }
        else if(deadend_up.ison()){
            LED.on();
        }
        else if(deadend_do.ison()){
            LED.on();
        }
        else{
            LED.off();
        }
        _delay_ms(1);
    }
    return 0;
}
