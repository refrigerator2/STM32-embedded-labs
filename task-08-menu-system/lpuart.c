#include "lpuart.h"
#include "hardware.h"

#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))
#define RCC_APB1ENR2  (*(volatile uint32_t*)(0x40021000 + 0x5C))
#define NVIC_ISER2    (*(volatile uint32_t*)(0xE000E100 + 2 * 4))

#define LPUART_CR1_UE     (1 << 0)
#define LPUART_CR1_RE     (1 << 2)
#define LPUART_CR1_TE     (1 << 3)
#define LPUART_CR1_RXNEIE (1 << 5)
#define LPUART_ISR_RXNE   (1 << 5)
#define LPUART_ISR_TXE    (1 << 7)

void LPUART_init(void) {
    RCC_AHB2ENR  |= (1 << 2);
    RCC_APB1ENR2 |= (1 << 0);

    volatile uint32_t tmpreg = RCC_AHB2ENR;
    (void)tmpreg;

    GPIOC->MODER &= ~((3 << 0) | (3 << 2));
    GPIOC->MODER |=  ((2 << 0) | (2 << 2));

    GPIOC->PUPDR &= ~((3 << 0) | (3 << 2));
    GPIOC->PUPDR |=  ((1 << 0) | (1 << 2));

    GPIOC->AFR[0] &= ~(0xFF);
    GPIOC->AFR[0] |=  0x88;

    LPUART1->CR1 &= ~LPUART_CR1_UE;
    LPUART1->BRR = 8889;

    LPUART1->CR1 |= LPUART_CR1_RXNEIE;
    NVIC_ISER2   |= (1 << 6);

    LPUART1->CR1 |= LPUART_CR1_UE;
    LPUART1->CR1 |= LPUART_CR1_TE | LPUART_CR1_RE;
}

void LPUART_SendChar(char data) {
    while (!(LPUART1->ISR & LPUART_ISR_TXE));
    LPUART1->TDR = (uint32_t)data;
}

void LPUART_ReceiveChar(char* data) {
    while (!(LPUART1->ISR & LPUART_ISR_RXNE));
    *data = (char)(LPUART1->RDR & 0xFF);
}

void LPUART_SendString(const char* str) {
    while (*str) {
        LPUART_SendChar(*str++);
    }
}
