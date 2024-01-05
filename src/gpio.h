#pragma once


#include <avr/io.h>

typedef struct GPIO{
	volatile uint8_t  PIN; // LSB
	volatile uint8_t DDR;
	volatile uint8_t PORT;
}GPIO;

constexpr int GPIOBaseAddr = 0x23;

#define VALID_PIN(x) 0 <= x && x <= 7

enum ePin { zero, one, two, three, four, five, six, seven };
enum ePort { B, C, D };
enum eDirection { IN, OUT };
enum eResistor { FLOATING, PULLUP };

#define B_CODE 66

GPIO* get_register_from_char(const char port);

GPIO* get_register(ePort port);

void gpio_init(GPIO* gpio, ePin n, eDirection dir, eResistor r);

void set_direction(GPIO* gpio, eDirection dir, int n);

// writing
void toggle(GPIO* gpio, int n);
void set(GPIO* gpio, int n);
void reset(GPIO* gpio, int n);

// reading
uint8_t read(GPIO* gpio, int n);