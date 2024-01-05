#pragma once
#include <stdint.h>

#define CAPACITY 32

typedef struct CircularBuffer{
    char buffer[CAPACITY][CAPACITY]; 
    uint8_t read_index;
    uint8_t write_index;
    uint8_t length;
} CircularBuffer;


typedef struct lifo_iterator{
    CircularBuffer* buff;
    int i;
    int i_bounds;
    bool first_pass;
}lifo_iterator;


void init(CircularBuffer* buff);

void write(CircularBuffer* buff, const char* s);

uint8_t read(CircularBuffer* buff, char* s);

lifo_iterator get_lifo_iterator(CircularBuffer* buff);

int8_t peek_lifo_forward(lifo_iterator* itr, char* s);

int8_t peek_lifo_back(lifo_iterator* itr, char* s);
