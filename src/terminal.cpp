#include "terminal.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "circularbuffer.h"
#include "state_machine.h"
#include "usart.h"
#include "gpio.h"
#include "command.h"
#include "timer.h"

#define MAX_COMMAND_LENGTH 16
#define MAX_TOKENS 16


static lifo_iterator iter;

CircularBuffer history;
static char rx_buffer[CAPACITY] = {'\0'};

/* interrupt flags */
static volatile bool user_enter = false;
static volatile bool up_key = false;
static volatile bool down_key = false;


void backspace(int n){

    for (int i = 0; i < n; i++){
        print("\b \b");
    }
}


static void go_up(int16_t event){ up_key = true; }
static void go_down(int16_t event){ down_key = true; }


const static StateTransition_t up_sequence[] = {
    {0, ESCAPE_KEY, pass, 1},
    {1, -85, pass, 2},
    {2, -1, go_up , 0},
};

const static StateTransition_t down_sequence[] = {
    {0, ESCAPE_KEY, pass, 1},
    {1, 43, pass, 2},
    {2, -1, go_down , 0},
};
static int num_terminal_characters = 0;

void init_terminal(){
    init(&history);

    usart_init(eight_bit, SYNCH, ODD, one_bit, 9600_baud);
    sei();

    print(">> ");
}

void reset_terminal_line(char cmd[]){
    println();
    print(">> ");

    memset(rx_buffer, '\0', CAPACITY);
    num_terminal_characters = 0;
    user_enter = false;

    // store only if different from previous command
    if (strcmp(cmd, history.buffer[history.write_index-1]) != 0){
        write(&history, cmd);
    }

    iter = get_lifo_iterator(&history);
}


ISR(USART_RX_vect){
    
    char data = UDR0;
    
    /* sequence detectors for keyboard control */

    static StateMachine_t up_key_sm  = {
        .name="up",
        .table=up_sequence,
        .tbsize=3,
        .state=0,
        .default_state=0,
    };

    static StateMachine_t down_key_sm  = {
        .name="down",
        .table=down_sequence,
        .tbsize=3,
        .state=0,
        .default_state=0,
    };

    if(update_sequencer(&up_key_sm, data) || update_sequencer(&down_key_sm, data)){

        return;
    }
    
    // stop any ongoing watch timers
    if (data == CTRL_C) {
        TIM2_SK->TOIE = 0;
        reset_terminal_line(rx_buffer);
        return;
    }
    
    switch (data) {
    
    // process user input
    case ENTER_KEY:
        
        if(rx_buffer[0] != '\0'){
            user_enter = true;
        }

        break;

    // delete single character
    case BACKSPACE:

        if (num_terminal_characters == 0){
            break;
        }


        if (num_terminal_characters != 0){
            num_terminal_characters--;
            rx_buffer[num_terminal_characters] = '\0';
            backspace(1);
        }

        break;

    // delete entire line
    case CTRL_BACKSPACE:

        backspace(num_terminal_characters);
        num_terminal_characters = 0;

    // echo to terminal 
    default:

        // printable ascii characters
        if (data < 32 || 127 < data){
            break;
        }

        // store data and echo to terminal
        rx_buffer[num_terminal_characters] = data;
        UDR0 = data; 

        num_terminal_characters++;

        break;
    }
}


void handle_vertical_arrow_keys(int is_up){

    char tmp[32] = {'\0'};

    int stat = is_up ? peek_lifo_forward(&iter, tmp) :  peek_lifo_back(&iter, tmp);

    if (stat == -1){
        return;
    } 
    
    // replace current command with one from history
    backspace(num_terminal_characters);
    print(tmp);

    // update the receive uart buffer
    num_terminal_characters = strlen(tmp);
    strcpy(rx_buffer, tmp);

    // reset flags
    down_key = false;
    up_key = false;
}

void run_terminal(){
    
    char* tokens[MAX_TOKENS];
    int token_count;

    while(1){

        if (user_enter){

            char cmd[32] = {'\0'};
            strcpy(cmd, rx_buffer);

            if (!command_info(rx_buffer, tokens, &token_count)) continue;

                    parse_gpio_commands(&tokens[0]);

            reset_terminal_line(cmd);

        }
        else if(up_key){

            handle_vertical_arrow_keys(true);
        }
        else if(down_key){

            handle_vertical_arrow_keys(false);
        }
    }

}