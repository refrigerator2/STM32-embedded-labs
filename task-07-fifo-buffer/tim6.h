#pragma once
#include "gpio.h"
#define RCC_APB1ENR1  (*(volatile uint32_t*)(0x40021000 + 0x58))
#define PWR_CR2       (*(volatile uint32_t*)(0x40007000 + 0x04))
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))

#define GPIOB  ((GPIO_t*)0x48000400)
#define GPIOG  ((GPIO_t*)0x48001800)

#define DELAY 300000
#define TIM6 ((TIM6_t *)0x40001000)


typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t DIER;
    volatile uint32_t reserved;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t reserved1;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM6_t;

void init_tim6();
void init_gpios();
void delay_ms_tim6(volatile uint32_t ms);
void display_number(int32_t number);
