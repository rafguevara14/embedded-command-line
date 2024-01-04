#pragma once


#include <avr/io.h>

typedef struct GPIO{
	volatile uint8_t  PIN; // LSB
	volatile uint8_t DDR;
	volatile uint8_t PORT;
}GPIO;

constexpr int GPIOBaseAddr = 0x23;

enum pin { zero, one, two, three, four, five, six, seven };
enum port { B, C, D };
enum direction { IN, OUT };
enum resistor { FLOATING, PULLUP };


GPIO* get_register(port port);

void gpio_init(GPIO* gpio, pin n, direction dir, resistor r);

// writing
void toggle(GPIO* gpio, int n);
void set(GPIO* gpio, int n);
void reset(GPIO* gpio, int n);

// reading
uint8_t read(GPIO* gpio, int n);