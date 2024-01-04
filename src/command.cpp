#include "command.h"

#include <string.h>
#include <stdio.h>

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