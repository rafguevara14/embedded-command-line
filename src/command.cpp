#include "command.h"
#include "arduino_uno.h"
#include "isr.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// to avoid lambda trickiness and capture list scopes
static GPIO* gpio_port;
static int gpio_pin;


static const GPIOCommand GPIO_CMD_MAP[] = {
    {"toggle",     [](){ toggle(gpio_port, gpio_pin); }},
    {"read",       [](){ println(); printd(read(gpio_port, gpio_pin)); }},
    {"set",        [](){ set(gpio_port, gpio_pin); } },
    {"reset",      [](){ reset(gpio_port, gpio_pin); } },
    {"config-in",  [](){ set_direction(gpio_port, IN, gpio_pin); }},
    {"config-out", [](){ set_direction(gpio_port, OUT, gpio_pin); }},
    {"watch-read", [](){  
        println();
        register_irq(isr_index::TIMER2_OVRFLW, [](){
            printd(read(gpio_port, gpio_pin));
            println();
        });

        interrupt_configure(reinterpret_cast<Timer8*>(TIM2_BASE), TIM2_SK);

    }},

    {"watch-toggle", [](){  

        register_irq(isr_index::TIMER2_OVRFLW, [](){
            toggle(gpio_port, gpio_pin);
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
                gpio_port = gpio;
                gpio_pin = pinmap.pin;
                row->action(); 
            }

            return row;
        }
    }
    return NULL;
}

int to_int(char* str){
    return (int)strtol(str, (char **)NULL, 10);
}
