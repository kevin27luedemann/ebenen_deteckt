//this example runs with 2 shift registers

#define F_CPU 8000000
#define BAUD 9600

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "seven_seg.h"
#include "Input.h"
#include "Output.h"
//#include "l74hc595b.h"
#include "tm1637.h"
#include "DHT22.h"
DHT22 dht22(0, PD2, &DDRD, &PORTD, INT0, ISC00, ISC01, INTF0, &EIMSK, &EICRA, &EIFR, CS21, &OCR2A, &TCNT2, &TCCR2B);
#include "com.h"

//l74hc595b shift_reg(&DDRB,&PORTB,1,2,3,1);
//seven_seg seg(4,&DDRC,&PORTC,0,&shift_reg);
tm1637 seg;
Input taster(&DDRD,&PORTD,&PIND,6,true);
Output LED(&DDRB,&PORTB,0);
#define WEATHER_FLAG 0
#define DISP_UPDATE 1
uint8_t flag_reg;

void send_weather();

ISR(TIMER2_COMPA_vect){
    dht22.ISR_TIMER_TOUTINE();
}

ISR(INT0_vect){
   dht22.ISR_INT_ROUTINE();
}

/*
ISR(TIMER0_OVF_vect){
    if(seg.ison){
        seg.next_segement();
    }
    TCNT0 = 100;
}
*/

ISR(USART_RX_vect){
    uint8_t temp = uart_getc();
    static uint8_t count = 0;
    if(temp=='d'){
        uart_putc(taster.ison()+'0');
    }
    else if(temp=='w'){
        dht22.DHT22_StartReading();
        flag_reg |= (1<<WEATHER_FLAG);
    }
    else{
        if(count==4){
            //seg.dot_pos = temp - '0';
            flag_reg |= (1<<DISP_UPDATE);
            count = 0;
        }
        else{
            //seg.set_number(count,temp-'0');
            seg.segments[count] = temp-'0';
            count++;
        }
    }
    
}

int main(void) {

    uart_init();
    flag_reg = 0;

    //init timer fuer segment
    //TIMSK0 |= (1<<TOIE0);
    //TCCR0B |= (1<<CS02);// | (1<<CS00);
    //init timer fuer dht22
    //intialize timer0 for DHT22 Sensors
    TCCR2A = (1 << WGM21);
    TIMSK2 = (1 << OCIE2A);
    sei();

    /*
    seg.on();
    seg.dot_pos = 1;
    seg.set_number(0,0);
    seg.set_number(1,0);
    seg.set_number(2,0);
    seg.set_number(3,0);
    */
    seg.setSegments();

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
        if((flag_reg&(1<<WEATHER_FLAG))){send_weather();flag_reg&=~(1<<WEATHER_FLAG);}
        if((flag_reg&(1<<DISP_UPDATE))){seg.setSegments();flag_reg&=~(1<<DISP_UPDATE);}
	}

}

void send_weather(){
   uint8_t status = 0;
   while(status != dht22.DHT_DATA_READY && status != dht22.DHT_ERROR_NOT_RESPOND && status != dht22.DHT_ERROR_CHECKSUM){
   status = dht22.DHT22_CheckStatus();
   }
   if(status == dht22.DHT_ERROR_NOT_RESPOND){
        uart_puts("no_respond!\n");
   }
   else{
       if(dht22.temperature_integral<0){
          uart_putc('-');
          uart_putc('0'+(-1)*dht22.temperature_integral/10);
       }
       else{
          uart_putc('+');
          uart_putc('0'+dht22.temperature_integral/10);
       } 
       uart_putc('0'+dht22.temperature_integral%10);
       uart_putc('.');
       uart_putc('0'+dht22.temperature_decimal);
       uart_putc('\t');
       uart_putc('0'+dht22.humidity_integral/100%10);
       uart_putc('0'+dht22.humidity_integral/10%10);
       uart_putc('0'+dht22.humidity_integral%10);
       uart_putc('.');
       uart_putc('0'+dht22.humidity_decimal);
       uart_putc('\n');
    }
}
