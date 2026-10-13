#include <stdint.h>
#include <stdlib.h>

#define SIZE 16

struct FIFO{
    uint32_t first_elem_index;
    uint32_t last_elem_index;
    uint32_t capacity;
    char data[SIZE];
};
extern struct FIFO fifo;

void fifo_init (struct FIFO *Fifo);
int8_t is_fifo_empty (struct FIFO *Fifo);
int8_t is_fifo_full (struct FIFO *Fifo);
int8_t fifo_put (struct FIFO *Fifo, char Data);
int8_t fifo_get (struct FIFO *Fifo, char *Data);

