#include "adc.h"

void adc_set_channel(adc_channel channel){
    adc_disable();
    ADMUX |= channel << MUX0;
    adc_enable();
}

void adc_init(voltage_ref vref, adc_channel channel, int interrupt, adc_prescaler prescaler){

    // initializing channel
    ADMUX |= vref << REFS1;
    ADMUX |= adc_resolution::TEN_BIT_RESOLUTION << ADLAR;
    ADCSRA |= prescaler << ADPS2;
    adc_set_channel(channel);

    adc_enable();
    adc_interrupt_enable(interrupt);

}

void adc_enable(){
    ADCSRA |= 1 << ADEN;
}

void adc_disable(){
    ADCSRA &= ~(1 << ADEN);
}

void adc_interrupt_enable(int interrupt){

    ADCSRA |= interrupt << ADIE;
    // if interrupts enabled, immediately start conversions
    ADCSRA |= interrupt << ADSC;
}

uint16_t adc_get_data(){

    // Start conversion
    ADCSRA |= 1 << ADSC;
    while(ADCSRA & (1 << ADSC));
    
    // assuming 10 bit resolution
    return ADC;
}
