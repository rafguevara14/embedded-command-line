
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "circularbuffer.h"
#include "state_machine.h"
#include "usart.h"
#include "gpio.h"
#include "command.h"
#include "terminal.h"


int main()
{
    
    init_terminal();

    while(1){
        run_terminal();
    }
    
    return 0;
}
