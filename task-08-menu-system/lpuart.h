#ifndef LPUART_H
#define LPUART_H

#include <stdint.h>

#define LPUART1_BASE 0x40008000

// struktura rejestrów portu szeregowego
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t BRR;
    volatile uint32_t GTPR;
    volatile uint32_t RTOR;
    volatile uint32_t RQR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t RDR;
    volatile uint32_t TDR;
} LPUART_t;

#define LPUART1 ((LPUART_t*)LPUART1_BASE)

void LPUART_init(void);
void LPUART_SendChar(char data);
void LPUART_ReceiveChar(char* data);
void LPUART_SendString(const char* str);

#endif // LPUART_H
