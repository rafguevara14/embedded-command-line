#include "circularbuffer.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


// typedef struct CircularBuffer{
//     char** buffer; 
//     uint8_t read_index;
//     uint8_t write_index;
//     uint8_t buff_length;
//     uint8_t capacity;
// } CircularBuffer;



static char* strings[11];
CircularBuffer buff;


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
	
	// Find newline character and remove
	if ((strlen(command) > 0) && (command[strlen (command) - 1] == '\n'))
		command[strlen (command) - 1] = '\0';

	return *token_count > 0;
}

void test_circularbuffer(){
    init(&buff);

    write(&buff, "hello1");
    write(&buff, "hello2");
    write(&buff, "hello3");
    write(&buff, "hello4");
    write(&buff, "hello5");

    write(&buff, "hello6");
    write(&buff, "hello7");
    write(&buff, "hello8");
    write(&buff, "hello9");
    write(&buff, "hello10");

    for (int i = 0; i < 10; i++){
        char buffer[32];
        read(&buff, buffer);

        printf("%s\n", buffer);
    }


}

void test_peek(){

    init(&buff);

    write(&buff, "hello1");
    write(&buff, "hello2");
    write(&buff, "hello3");
    write(&buff, "hello4");
    write(&buff, "hello5");

    write(&buff, "hello6");
    write(&buff, "hello7");
    write(&buff, "hello8");
    write(&buff, "hello9");
    write(&buff, "hello10");


    lifo_iterator iter = get_lifo_iterator(&buff);

    for (int i = 0; i < 20; i++){
        char buffer[32];

        assert(peek_lifo_forward(&iter, buffer) != -1);

        printf("%s\n", buffer);
    }

    printf("Going backwards!\n");

    // iter = get_lifo_iterator(&buff);
    for (int i = 0; i < 20; i++){
        char buffer[32];

        assert(peek_lifo_back(&iter, buffer) != -1);

        printf("%s\n", buffer);
    }

}

int main() {



    // test_circularbuffer();
    // test_peek();

    int x = 5;
    x += 0 ? 1:0;
    printf("%d\n", x);




    return 0;
}
