#include "command.h"
#include "arduino_uno.h"
#include "isr.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static GPIO* gportwatch;
static int gpinwatch;

static const GPIOCommand GPIO_CMD_MAP[] = {
    {"toggle", toggle},
    {"read", [](GPIO* g, int p){ println(); printd(read(g,p)); }},
    {"set", set},
    {"reset", reset},
    {"config-in", [](GPIO* g, int p){ set_direction(g, IN, p); }},
    {"config-out", [](GPIO* g, int p){ set_direction(g, OUT, p); }},


    {"watch-read", [](GPIO* g, int p){  

        gportwatch = g;
        gpinwatch = p;

        println();
        register_irq(isr_index::TIMER2_OVRFLW, [](){
            printd(read(gportwatch, gpinwatch));
            println();
        });

        interrupt_configure(reinterpret_cast<Timer8*>(TIM2_BASE), TIM2_SK);
    }},

    {"watch-toggle", [](GPIO* g, int p){  
        gportwatch = g;
        gpinwatch = p;
        register_irq(isr_index::TIMER2_OVRFLW, [](){
            toggle(gportwatch, gpinwatch);
        });

        interrupt_configure(reinterpret_cast<Timer8*>(TIM2_BASE), TIM2_SK);
    }},
};


// modify the command argument to include the command and arguments
int parse_command(char* command, char *tokens[])
{
	char delimiters[] = " ";
	int token_count = 0;
	char* token = strtok(command, delimiters);

	while (token != NULL) 
	{
		tokens[token_count++] = token;
		token = strtok(NULL, delimiters);
	}

	tokens[token_count] = NULL;
	return token_count;
}

bool command_info(char* command, char** tokens, int* token_count)
{
	*token_count = parse_command(command, tokens);
	
	return *token_count > 0;
}

const GPIOCommand* parse_gpio_commands(char** tokens){

    for (int i = 0; i < sizeof(GPIO_CMD_MAP)/sizeof(GPIOCommand); i++){

        const GPIOCommand* row = &GPIO_CMD_MAP[i];

        // look up command in command table
        if (strcmp(tokens[0], row->command) == 0){

            char port = tokens[1][0];
            int pin = to_int(&tokens[1][1]);

            // translate dev board pinout to chip pinout
            auto pinmap = dev_to_pin(port, pin);
            auto gpio = get_register(pinmap.port);

            if (VALID_PIN(pinmap.pin)){
                row->action(gpio, pinmap.pin); 
            }

            return row;
        }
    }
    return NULL;
}

int to_int(char* str){
    return (int)strtol(str, (char **)NULL, 10);
}