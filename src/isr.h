#pragma once


enum isr_index{
	TIMER0_OVRFLW,
	TIMER1_OVRFLW,
	TIMER2_OVRFLW,
	// USART_RX,

	END_OF_INDEX,
};
using isr_handler = void(*)();
void register_irq(isr_index index, isr_handler isr);
void enable_interrupts();

