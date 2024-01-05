#include "gpio.h"

GPIO* get_register_from_char(const char p){
    return get_register(static_cast<ePort>(p-B_CODE));
}

GPIO* get_register(ePort port){
    return (GPIO*)(GPIOBaseAddr + port);
}

void gpio_init(GPIO* gpio, ePin n, eDirection dir, eResistor r) { 

    set_direction(gpio, dir, n);

    // set resistor
    switch (r)
    {
        case FLOATING:  gpio->PIN |= (r << n); 
        case PULLUP: gpio->PIN &= ~(r << n); 
    }
}

//config
void set_direction(GPIO* gpio, eDirection dir, int n) {
    switch (dir) {
        case IN:  gpio->DDR &= ~(1 << n);
        case OUT: gpio->DDR |= (1 << n); 
    }
}

// writing
void toggle(GPIO* gpio, int n) { gpio->PIN  |= 1 << n; }
void set(GPIO* gpio, int n)    { gpio->PORT |= 1 << n; }
void reset(GPIO* gpio, int n)  { gpio->PORT &= ~(1 << n); }

// reading
uint8_t read(GPIO* gpio, int n) { return (gpio->PIN & (1 << n)) >> n; }