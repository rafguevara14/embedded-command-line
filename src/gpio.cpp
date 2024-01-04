#include "gpio.h"

GPIO* get_register(port port){
    return (GPIO*)(GPIOBaseAddr + port);
}

void gpio_init(GPIO* gpio, pin n, direction dir, resistor r) { 

    // set output direction
    switch (dir)
    {
        case IN:  gpio->DDR &= ~(1 << n);
        case OUT: gpio->DDR |= (1 << n); 
    }

    // set output direction
    switch (r)
    {
        case FLOATING:  gpio->PIN |= (r << n); 
        case PULLUP: gpio->PIN &= ~(r << n); 
    }
}

// writing
void toggle(GPIO* gpio, int n) { gpio->PIN  |= 1 << n; }
void set(GPIO* gpio, int n)    { gpio->PORT |= 1 << n; }
void reset(GPIO* gpio, int n)  { gpio->PORT &= ~(1 << n); }

// reading
uint8_t read(GPIO* gpio, int n) { return gpio->PIN & (1 << n); }