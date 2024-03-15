#include "timer.h"

void init_timer(Timer8* timer, int base, uint8_t prescale) {
    timer = reinterpret_cast<Timer8*>(base);
    timer->TCCRB.CS2 = prescale;
}
	
void interrupt_configure(Timer8* const timer, TIMSK* sk) {
    sk->TOIE = 1;

    timer->TCNT = 0;
}

uint8_t counter(const Timer8* const timer) { 
    return timer->TCNT;
}

uint8_t period(const Timer8* const timer) { 
    return TIMER_PERIOD_MS(timer->TCCRB.CS2);
}

