#pragma once
#include "gpio.h"

#define GPIOC ((GPIO_t*)0x48000800)
#define LPUART ((LPUART_t*)0x40008000)
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))
#define RCC_APB1ENR2  (*(volatile uint32_t*)(0x40021000 + 0x5C))
#define NVIC_ISER2    (*(volatile uint32_t*)(0xE000E108))
#include "fifo.h"


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



void LPUART_init(void);
void LPUART_SendChar(unsigned char data);
void LPUART_ReceiveChar(unsigned char* data);
void LPUART_SendString(unsigned char* data);
