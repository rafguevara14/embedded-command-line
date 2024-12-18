#pragma once
#include <avr/interrupt.h>
#include <avr/io.h>

constexpr int operator"" _baud(unsigned long long input) 
{
	const float f = ((F_CPU)/(input*16.0)) - 1;
	const int i = static_cast<int>(f);
    return f > i ? i + 1 : i;
}

constexpr int baud_check = 2400_baud;
static_assert(baud_check == 416, "Baud rate calculation incorrect. Please refer to pg165 of the datasheet.");


enum size {
    five_bit=0b000,
    six_bit=0b100,
    seven_bit=0b010,
    eight_bit=0b110,
    nine_bit=0b111
};

enum stop_bit {
    one_bit=0,
    two_bit
};

enum parity {
    DISABLE=0b00,
    EVEN=0b01, ODD=0b11,
};

enum mode {
    ASYNC=0b00,
    SYNCH=0b10,
    MSPI=0b11,
};

void usart_init(size charsize, mode m, 
	parity p, stop_bit stopbit,
	uint16_t baud_rate);

void put(char c); 

void print(const char* c);
void println(const char* c);
void println();
void printd(int d);
void printud(uint16_t d);