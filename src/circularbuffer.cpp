#include "circularbuffer.h"
#include <string.h>


void init(CircularBuffer* buff){

    buff->read_index = 0;
    buff->write_index = 0;
    buff->length = 0;

    memset(buff->buffer, '\0', sizeof(buff->buffer));
}

void write(CircularBuffer* buff, const char* s){

    if (buff->length != CAPACITY){
        // do nothing...overwrite
        buff->length++;
    }

    strcpy(buff->buffer[buff->write_index], s);

    buff->write_index = (buff->write_index+1) % CAPACITY;

}

uint8_t read(CircularBuffer* buff, char* s){

    if(buff->length == 0){
        return 0;
    }

    strcpy(s, buff->buffer[buff->read_index]);

    buff->read_index = (buff->read_index+1) % CAPACITY;
    buff->length--;

    return 1;
}


lifo_iterator get_lifo_iterator(CircularBuffer* buff){
    return (lifo_iterator){
        .buff = buff,
        .i = buff->write_index-1, // start at the most recent write, work backwards
        .i_bounds = buff->write_index,
    };
}

int8_t peek_lifo_forward(lifo_iterator* itr, char* s){

    CircularBuffer* b = itr->buff;
    
    if (b->length == 0){
        return -1;
    }

    strcpy(s, b->buffer[itr->i]);

    bool bounds = (itr->i == 0);
    itr->i = bounds ? itr->i : itr->i-1;

    return !bounds;
}

int8_t peek_lifo_back(lifo_iterator* itr, char* s){

    CircularBuffer* b = itr->buff;

    if (b->length == 0){
        return -1;
    }



    strcpy(s, itr->buff->buffer[itr->i]);

    bool bounds = (itr->i == (itr->i_bounds-1));
    itr->i = bounds ? itr->i : itr->i+1;

    return !bounds;
}
