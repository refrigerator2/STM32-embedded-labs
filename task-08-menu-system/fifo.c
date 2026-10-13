#include "fifo.h"

void fifo_init(struct FIFO *Fifo) {
    Fifo->head = 0;
    Fifo->tail = 0;
    Fifo->count = 0;
}

uint8_t is_fifo_empty(struct FIFO *Fifo) {
    return (Fifo->count == 0) ? 1 : 0;
}

uint8_t is_fifo_full(struct FIFO *Fifo) {
    return (Fifo->count == FIFO_SIZE) ? 1 : 0;
}

void fifo_put(struct FIFO *Fifo, char Data) {
    if (!is_fifo_full(Fifo)) {
        Fifo->data[Fifo->tail] = Data;
        Fifo->tail = (Fifo->tail + 1) % FIFO_SIZE; // zapętlanie ogona
        Fifo->count++;
    }
}

void fifo_get(struct FIFO *Fifo, char *Data) {
    if (!is_fifo_empty(Fifo)) {
        *Data = Fifo->data[Fifo->head];
        Fifo->head = (Fifo->head + 1) % FIFO_SIZE; // zapętlanie głowy
        Fifo->count--;
    }
}
