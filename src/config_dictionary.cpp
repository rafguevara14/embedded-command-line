#include "config_dictionary.h"
#include "adc.h"
#include "usart.h"
#include "arduino_uno.h"

static const config_t config_default = {-1};

static config_t PIN_LUT[] = {config_default};

void update_configuration(PortPin pinout, config_t config){
    PIN_LUT[PIN_TO_ELEMENT(pinout)] = config;
}

void print_configuration(PortPin pinout){

    auto config = PIN_LUT[PIN_TO_ELEMENT(pinout)];

    println();
    print("Direction: "); printd(config.dir); println();
    print("Resistor: "); printd(config.res); println();
    print("Voltage Reference: "); printd(config.vref); println();
    print("ADC Prescaler: "); printd(config.prescaler); println();

}