#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

#define FIFO_SIZE 64

struct FIFO {
    char data[FIFO_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
};

void fifo_init(struct FIFO *Fifo);
uint8_t is_fifo_empty(struct FIFO *Fifo);
uint8_t is_fifo_full(struct FIFO *Fifo);
void fifo_put(struct FIFO *Fifo, char Data);
void fifo_get(struct FIFO *Fifo, char *Data);

#endif // FIFO_H
