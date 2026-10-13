#include "hardware.h"

// rejestry zasilania i zegarów
#define RCC_APB1ENR1  (*(volatile uint32_t*)(0x40021000 + 0x58))
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))
#define PWR_CR2       (*(volatile uint32_t*)(0x40007000 + 0x04))
#define NVIC_ISER1    (*(volatile uint32_t*)(0xE000E100 + 1 * 4))

volatile uint32_t sys_tick = 0; // nasz główny zegar systemowy

void Hardware_Init(void) {
    // włączenie zasilania VDDIO2 i zegarów dla portów B, C, D, E, G
    RCC_APB1ENR1 |= (1 << 28);
    PWR_CR2 |= (1 << 9);
    RCC_AHB2ENR |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 6);

    // port B (wyświetlacz anody, LED G)
    GPIOB->MODER &= ~((3<<4)|(3<<6)|(3<<8)|(3<<10)|(3<<16));
    GPIOB->MODER |=  ((1<<4)|(1<<6)|(1<<8)|(1<<10)|(1<<16));

    // port C (LED 0-3)
    GPIOC->MODER &= ~((3<<12)|(3<<14)|(3<<16)|(3<<18));
    GPIOC->MODER |=  ((1<<12)|(1<<14)|(1<<16)|(1<<18));

    // port D (LED 5, LED B, LED R)
    GPIOD->MODER &= ~((3<<6)|(3<<24)|(3<<26));
    GPIOD->MODER |=  ((1<<6)|(1<<24)|(1<<26));

    // port E (LED 4,6,7 - wyjścia, Joy - wejścia z pull-up)
    GPIOE->MODER &= ~((3<<8)|(3<<10)|(3<<12) | (3<<0)|(3<<2)|(3<<4)|(3<<6)|(3<<30));
    GPIOE->MODER |=  ((1<<8)|(1<<10)|(1<<12));
    GPIOE->PUPDR &= ~((3<<0)|(3<<2)|(3<<4)|(3<<6)|(3<<30));
    GPIOE->PUPDR |=  ((1<<0)|(1<<2)|(1<<4)|(1<<6)|(1<<30));

    // port G (wyświetlacz segmenty)
    GPIOG->MODER &= ~((3<<0)|(3<<2)|(3<<4)|(3<<6)|(3<<8)|(3<<10)|(3<<12));
    GPIOG->MODER |=  ((1<<0)|(1<<2)|(1<<4)|(1<<6)|(1<<8)|(1<<10)|(1<<12));

    // konfiguracja Timera 6 (przerwanie co 1 ms)
    RCC_APB1ENR1 |= (1 << 4);
    TIM6->PSC = 3999;
    TIM6->ARR = 1;
    TIM6->DIER |= (1 << 0);
    NVIC_ISER1 |= (1 << 22); 
    TIM6->CR1 |= (1 << 0);
}

// obsługa przerwania od Timera 6

