#include "fifo.h"

struct FIFO fifo;


void fifo_init (struct FIFO *Fifo){
    Fifo->first_elem_index = 0;
    Fifo->last_elem_index = 0;
    Fifo->capacity = 0;
}
int8_t is_fifo_empty (struct FIFO *Fifo){
    return Fifo->capacity == 0;
}
int8_t is_fifo_full(struct FIFO *Fifo)
{
     return Fifo->capacity == SIZE;
}

int8_t fifo_put (struct FIFO *Fifo, char Data){
    if(is_fifo_full(Fifo)){
        return 1;
    }
    *(Fifo->data+Fifo->last_elem_index) = Data;
    Fifo->capacity+=1;
    Fifo->last_elem_index = (Fifo->last_elem_index + 1) % SIZE;
    return 0;
}
int8_t fifo_get (struct FIFO *Fifo, char *Data){
    if (is_fifo_empty(Fifo))
        return 1;

    *Data = *(Fifo->data+Fifo->first_elem_index);
    Fifo->capacity-=1;
    Fifo->first_elem_index = (Fifo->first_elem_index + 1) % SIZE;
    return 0;
}

