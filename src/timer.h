#pragma once 
#include "stdint.h"

#include <avr/io.h>

enum compare_mode{
	DISCONNECT,
	TOGGLE,
	CLEAR,
	SET
};

using vregister = uint8_t volatile;

union TCCRnA{
    struct{
        vregister WGM : 2;
        vregister RESERVED : 2;
        vregister COMB : 2;
        vregister COMA : 2;
    };
    vregister port;
};

union TCCRnB{
    struct{
        vregister CS2 : 3;
        vregister WGM2 : 1;
        vregister RESERVED : 2;
        vregister FOCB : 1;
        vregister FOCA : 1;
    };
    vregister port;
};

union TIMSK{
    struct{
        vregister TOIE  : 1;
        vregister OCIEA : 1;
        vregister OCIEB : 1;
        vregister RESERVED : 5;
    };
    vregister port;
};


union TIFR{
    struct{
        vregister TOV  : 1;
        vregister OCFA : 1;
        vregister OCFB : 1;
        vregister RESERVED : 5;
    };
    vregister port;
}; 

typedef struct{
	TCCRnA TCCRA;
	TCCRnB TCCRB;
	vregister TCNT;
	vregister OCRA;
	vregister OCRB;
}Timer8;

namespace clock_select0 {
	enum cs{
		NO_SOURCE,
		CLOCKIO,
		PRESCALE_8,
		PRESCALE_64,
		PRESCALE_256,
		PRESCALE_1024,
		EXT_FALLING,
		EXT_RISING
	};
};

namespace clock_select2 {
	enum cs{
		NO_SOURCE,
		CLOCKIO,
		PRESCALE_8,
		PRESCALE_32,
		PRESCALE_64,
		PRESCALE_128,
		PRESCALE_256,
		PRESCALE_1024,
	};
}
constexpr int TIM2_BASE = 0xB0;
TIMSK* const TIM2_SK = reinterpret_cast<TIMSK*>(0x70);
TIFR* const TIM2_FR = reinterpret_cast<TIFR*>(0x37);

constexpr float TIMER_PERIOD_MS(float prescale) {
    return 1000.0*(255.0*prescale)/F_CPU;
}

void init_timer(Timer8* timer, int base, uint8_t prescale);
	
void interrupt_configure(Timer8* const timer, TIMSK* sk);

uint8_t counter(const Timer8* const timer); 

uint8_t period(const Timer8* const timer); 
