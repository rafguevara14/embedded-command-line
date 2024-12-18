#pragma once

#include "gpio.h"
#include "usart.h"

typedef void (*gpio_action)();

typedef struct {
    const char* command;
    gpio_action action;
}GPIOCommand;


// modify the command argument to include the command and arguments
int parse_command(char* command, char *tokens[]);

bool command_info(char* command, char** tokens, int* token_count);

const GPIOCommand* parse_gpio_commands(char** tokens);

int to_int(char* str);