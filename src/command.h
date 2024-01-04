#pragma once

// modify the command argument to include the command and arguments
int parse_command(char* command, char *tokens[]);

bool command_info(char* command, char** tokens, int* token_count);
