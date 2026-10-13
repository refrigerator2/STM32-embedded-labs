#include "lpuart.h"

void LPUART_init(void) {
    RCC_AHB2ENR |= (1 << 2);
    RCC_APB1ENR2 |= (1 << 0);

    GPIOC->MODER &= ~((3 << 0) | (3 << 2));
    GPIOC->MODER |= ((2 << 0) | (2 << 2));

    GPIOC->PUPDR &= ~((3 << 0) | (3 << 2));
    GPIOC->PUPDR |= ((1 << 0) | (1 << 2));

    GPIOC->AFRL &= ~(0xFF);
    GPIOC->AFRL |= 0x88;

    LPUART->CR1 &= ~1;

    LPUART->BRR = 8889;

    LPUART->CR1 |= (1 << 0);
    LPUART->CR1 |= (1 << 3) | (1 << 2);
}

void LPUART_SendChar(unsigned char data) {
    while (!(LPUART->ISR & (1 << 7)));
    LPUART->TDR = data;
}

void LPUART_ReceiveChar(unsigned char* data) {
    while (!(LPUART->ISR & (1 << 5)));
    *data = (unsigned char)(LPUART->RDR & 0xFF);
}

void LPUART_SendString(unsigned char* data) {
    while (*data) {
        LPUART_SendChar(*data);
        data++;
    }
}
