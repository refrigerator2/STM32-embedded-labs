#include "tim6.h"

void init_tim6(){
	  RCC_APB1ENR1 |= (1 << 4);
	    TIM6->PSC = 3999;
	    TIM6->ARR = 1000;
	    TIM6->CR1 |= (1 << 0);
}
void init_gpios(){
	RCC_APB1ENR1 |= (1 << 28);
	PWR_CR2 |= (1 << 9);

	RCC_AHB2ENR |= (1 << 1) | (1 << 4) | (1 << 6);

    GPIOB->MODER &= ~((3 << 4) | (3 << 6) | (3 << 8) | (3 << 10));
    GPIOB->MODER |= ((1 << 4) | (1 << 6) | (1 << 8) | (1 << 10));

    GPIOG->MODER &= ~((3 << 0) | (3<<2) |(3 << 4) | (3 << 6) | (3 << 8) | (3 << 10) | (3 << 12) | (3 << 18));
    GPIOG->MODER |= ((1 << 0) | (1<<2) |(1 << 4) | (1 << 6) | (1 << 8) | (1 << 10) | (1 << 12) | (1 << 18));

}

const uint32_t segment_codes[10] = {
    0x3F, // 0: A,B,C,D,E,F
    0x06, // 1: B,C
    0x5B, // 2: A,B,D,E,G
    0x4F, // 3: A,B,C,D,G
    0x66, // 4: B,C,F,G
    0x6D, // 5: A,C,D,F,G
    0x7D, // 6: A,C,D,E,F,G
    0x07, // 7: A,B,C
    0x7F, // 8: A,B,C,D,E,F,G
    0x6F  // 9: A,B,C,D,F,G
};

void delay_ms_tim6(volatile uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        TIM6->SR &= (1<<0);
        while(!(TIM6->SR & 1));
    }
}

void display_number(int32_t number)
{
    if (number < 0 || number > 9) return;

    GPIOB->ODR &= ~(1 << 5);   // disable digit first

    GPIOG->ODR = (GPIOG->ODR & ~0x7F) | segment_codes[number];

    GPIOB->ODR |= (1 << 5);    // enable digit
	delay_ms_tim6(DELAY);
    GPIOB->ODR &= ~(1 << 5);   // disable digit first

}

