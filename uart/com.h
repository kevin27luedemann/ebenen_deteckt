/*
 * com.h
 */

#ifndef F_CPU
#error "F_CPU not defined"
#endif

#ifndef BAUD
#error "BAUD not defined"
#endif

#include <util/setbaud.h>

void uart_init(void){
    UBRRH   = UBRRH_VALUE;
    UBRRL   = UBRRL_VALUE;
	UCSRC   = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);	// 8Bit Frame
	UCSRB   = (1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
}

/* Zeichen senden*/
void uart_putc(unsigned char c)
{
    while (!(UCSRA & (1<<UDRE)))  /* warten bis Senden moeglich */
    {
    }                             

    UDR = c;                      /* sende Zeichen */
}

void uart_puts (char *s)
{
    while (*s)
    {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        uart_putc(*s);
        s++;
    }
}

/* Zeichen empfangen */
uint8_t uart_getc(void)
{
    while (!(UCSRA & (1<<RXC)))   // warten bis Zeichen verfuegbar
        ;
    return UDR;                   // Zeichen aus UDR an Aufrufer zurueckgeben
}

void uart_gets( char* Buffer, uint8_t MaxLen )
{
  uint8_t NextChar;
  uint8_t StringLen = 0;

  NextChar = uart_getc();         // Warte auf und empfange das nächste Zeichen

                                  // Sammle solange Zeichen, bis:
                                  // * entweder das String Ende Zeichen kam
                                  // * oder das aufnehmende Array voll ist
  while( NextChar != '\n' && StringLen < MaxLen - 1 ) {
    *Buffer++ = NextChar;
    StringLen++;
    NextChar = uart_getc();
  }

                                  // Noch ein '\0' anhängen um einen Standard
                                  // C-String daraus zu machen
  *Buffer = '\0';
}
