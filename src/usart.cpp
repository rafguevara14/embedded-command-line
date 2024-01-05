#include "usart.h"

#include <stdio.h>



void usart_init(size charsize, mode m, 
	parity p, stop_bit stopbit,
	uint16_t baud_rate)
{
	// enable tx/rx 
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
            

	// set character size and stop bit
	UCSR0C = (stopbit << USBS0) 
            | (charsize << UCSZ00) 
            | (m << UMSEL00) 
            | (p << UPM00);

	UCSR0B |= (charsize >> 2) << UCSZ02;

	UBRR0L |= baud_rate;
	UBRR0H |= baud_rate >> 8;

    // configure interrupts
	UCSR0B |= 1 << RXCIE0;
}


void put(char c) {	
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void print(const char* c) {

	while(*c) put(*c++);
}

void println(const char* c) {	

    print(c);

    put('\r');
    put('\n');
}

void println() {	
    println(" ");
}

void printd(int d){
    char buffer[5];
    sprintf(buffer, "%d", d);
    print(buffer);	
}
