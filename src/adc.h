#pragma once

#include <avr/io.h>


enum voltage_ref{
    AREF=0b0,
    VCC=0b1,
    ONEVONE_REF=0b11,
};

enum adc_channel{
    ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,
    TEMP_SENSOR,
    ONEVONE=0b1110,
    ZERO_V,
};

enum adc_prescaler{
    FACTOR_2=0b1,
    FACTOR_4,
    FACTOR_8,
    FACTOR_16,
    FACTOR_32,
    FACTOR_64,
    FACTOR_128,
};

enum adc_resolution{
    TEN_BIT_RESOLUTION,
    EIGHT_BIT_RESOLUTION,
};

void adc_init(voltage_ref vref, adc_channel channel, int interrupt, adc_prescaler prescaler);
void adc_set_channel(adc_channel channel);
void adc_interrupt_enable(int interrupt);
void adc_enable();
void adc_disable();
uint16_t adc_get_data();


