#ifndef LPUART_H
#define LPUART_H

#include <stdint.h>

#define GPIOC ((GPIO_t*)0x48000800)
#define LPUART ((LPUART_t*)0x40008000)
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))
#define RCC_APB1ENR2  (*(volatile uint32_t*)(0x40021000 + 0x5C))
#define GAP_BETWEEN_CAPITALS_AND_ORDINARY_IN_ASCII (25+7)
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



typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
    volatile uint32_t BRR;
    volatile uint32_t ASCR;
} GPIO_t;

void LPUART_init(void);
void LPUART_SendChar(unsigned char data);
void LPUART_ReceiveChar(unsigned char* data);
void LPUART_SendString(unsigned char* data);

#endif
