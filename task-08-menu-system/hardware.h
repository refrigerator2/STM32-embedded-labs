#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// struktura rejestrów GPIO dla bare-metal
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
} GPIO_TypeDef;

// struktura rejestrów Timera
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    uint32_t RESERVED0;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    uint32_t RESERVED1[3];
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM_TypeDef;

// adresy bazowe sprzętu
#define GPIOB ((GPIO_TypeDef *) 0x48000400)
#define GPIOC ((GPIO_TypeDef *) 0x48000800)
#define GPIOD ((GPIO_TypeDef *) 0x48000C00)
#define GPIOE ((GPIO_TypeDef *) 0x48001000)
#define GPIOG ((GPIO_TypeDef *) 0x48001800)
#define TIM6  ((TIM_TypeDef  *) 0x40001000)

extern volatile uint32_t sys_tick; // zmienna przechowująca czas (ms)

void Hardware_Init(void);

#endif
