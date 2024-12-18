#pragma once
#include "gpio.h"

// https://friedchips.io/en/Arduino,+ATMega328+port+manipulation+pin+port+mapping.html

#define D_CODE 68
#define B_CODE 66
#define A_CODE 65

typedef struct{
    ePort port;
    int pin;
}PortPin;

PortPin dev_to_pin(char port, int pin);