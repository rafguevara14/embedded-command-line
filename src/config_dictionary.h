#pragma once
#include "arduino_uno.h"

// ports B, C, D
// pins 0 to 7 
constexpr int PIN_TO_ELEMENT(PortPin pinout){
    return pinout.port * 8 + pinout.pin;
}

enum arduino_pins{
    B0,
    B1,
    B2,
    B3,
    B4,
    B5,
    B6,
    B7,

    C0,
    C1,
    C2,
    C3,
    C4,
    C5,
    C6,
    C7,

    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,

};

typedef struct{
    int dir;
    int res;
    int vref;
    int prescaler;
} config_t;


void update_configuration(PortPin pinout, config_t config);
void print_configuration(PortPin pinout);