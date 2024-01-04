
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "circularbuffer.h"
#include "state_machine.h"
#include "usart.h"
#include "gpio.h"
#include "command.h"


#define MAX_COMMAND_LENGTH 16
#define MAX_TOKENS 16
CircularBuffer buff;
static char user_string[CAPACITY] = {'\0'};
volatile bool user_enter = false;

enum{
    ENTER_KEY=13,
    BACKSPACE=127,
    BLANKSPACE=32,
    ESCAPE_KEY=27,
    CTRL_BACKSPACE=23
};

void pass(int16_t event){}

void backspace(int n){

    for (int i = 0; i < n; i++){
        print("\b \b");
    }
}

static bool up_key = false;
static bool down_key = false;

void go_up(int16_t event){ up_key = true; }
void go_down(int16_t event){ down_key = true; }


const static StateTransition_t up_sequence[] = {
    {0, ESCAPE_KEY, pass, 1},
    {1, -85, pass, 2},
    {2, -1, go_up , 0},
};

const static StateTransition_t down_sequence[] = {
    {0, ESCAPE_KEY, pass, 1},
    {1, 43, pass, 2},
    {2, -1, go_up , 0},
};

static int num_terminal_characters = 0;

ISR(USART_RX_vect){
    
    char data = UDR0;
    
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


    // char buffer[10];
    // sprintf(buffer, "%d\n", data);
    // print(buffer);

    switch (data) {
    
    case ENTER_KEY:
        println();
        print(">> ");
        
        if(user_string[0] != '\0'){
            user_enter = true;
        }

        break;

    case BACKSPACE:

        if (num_terminal_characters == 0){
            break;
        }


        if (num_terminal_characters != 0){
            num_terminal_characters--;
            user_string[num_terminal_characters] = '\0';
            backspace(1);
        }



        break;

    case CTRL_BACKSPACE:

        backspace(num_terminal_characters);
        num_terminal_characters = 0;

    default:
        // echo to terminal 

        // printable ascii characters
        if (data < 32 || 127 < data){
            break;
        }

        user_string[num_terminal_characters] = data;

        UDR0 = data; // read buffer and put back 

        num_terminal_characters++;
        break;
    }

}



int main()
{
    usart_init(eight_bit, SYNCH, ODD, one_bit, 9600_baud);
    sei();

    init(&buff);
    
    print(">> ");
    
    auto gpio = get_register(port::B);
    
    gpio_init(gpio, pin::five, direction::OUT, resistor::FLOATING);
    
    // DDRB |= 1<< DDB5;

    // PORTB |= 1 << 5;

    // split a line into tokens for parsing 
    char* tokens[MAX_TOKENS];
    int token_count;
    lifo_iterator iter =  get_lifo_iterator(&buff);
    int history_index = 0;

    while(1){
        if (user_enter){

            num_terminal_characters = 0;

            char command[32];
            strcpy(command, user_string);

            if (!command_info(user_string, tokens, &token_count)) continue;

            // led appears once in the beginning
            if (strcmp(tokens[0], "toggle") == 0){
                if (strcmp(tokens[1], "five") == 0){
                    toggle(gpio, pin::five);
                    if (strcmp(command, buff.buffer[buff.write_index-1]) != 0){
                        write(&buff, command);
                        iter = get_lifo_iterator(&buff);
                    }
                    history_index = 0;

                }

            }


            memset(user_string, '\0', CAPACITY);

            user_enter = false;
        }
        else if(up_key){

            char tmp[32] = {'\0'};

            int stat = peek_lifo_forward(&iter, tmp);

            if (stat == -1){
                continue;
            } 

            backspace(num_terminal_characters);
            print(tmp);
            char buffer[10] = {'\0'};
            sprintf(buffer, " (%d)", history_index);
            print(buffer);

            num_terminal_characters = strlen(tmp);
            num_terminal_characters += strlen(buffer);

            strcpy(user_string, tmp);

            up_key = false;
            
            if (stat){
                history_index++;
            }

        }
        else if(down_key){
            
            char tmp[32] = {'\0'};

            int stat = peek_lifo_back(&iter, tmp);

            if (stat == -1){
                continue;
            } 
            
            backspace(num_terminal_characters);
            print(tmp);

            char buffer[10] = {'\0'};
            sprintf(buffer, " (%d)", history_index);
            print(buffer);

            num_terminal_characters = strlen(tmp);

            num_terminal_characters += strlen(buffer);

            strcpy(user_string, tmp);
            down_key = false;
            if (stat){
                history_index--;
            }
        }
    
    }
    
    




    return 0;
}
