
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "isr.h"
#include "circularbuffer.h"
#include "state_machine.h"
#include "usart.h"
#include "gpio.h"
#include "command.h"
#include "terminal.h"
#include "timer.h"

int main()
{
    Timer8* timer = nullptr;
    init_timer(timer, TIM2_BASE, clock_select2::PRESCALE_1024);


    register_irq(isr_index::TIMER2_OVRFLW, [](){});

    // translate dev board pinout to chip pinout
    enable_interrupts();

    init_terminal();

    while(1){
        run_terminal();
    }
    
    return 0;
}
