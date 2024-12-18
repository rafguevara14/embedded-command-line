#include "isr.h"
#include <avr/interrupt.h>

static isr_handler isr_handlers[isr_index::END_OF_INDEX];

void register_irq(isr_index index, isr_handler isr)
{
	isr_handlers[index] = isr;
}

void enable_interrupts()
{
	sei();
}


ISR(TIMER0_OVF_vect) { 
	isr_handlers[isr_index::TIMER0_OVRFLW]();
}

ISR(TIMER1_OVF_vect) { 
	isr_handlers[isr_index::TIMER1_OVRFLW]();
}

ISR(TIMER2_OVF_vect) { 
	isr_handlers[isr_index::TIMER2_OVRFLW]();
}

ISR(ADC_vect) { 
	isr_handlers[isr_index::ADC_CONVERSION_CMPLT]();
}

// ISR(USART_RX_vect){
// 	isr_handlers[isr_index::USART_RX](); 
// }
