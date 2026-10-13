
#include <stdint.h>
#define RCC_APB1ENR1  (*(volatile uint32_t*)(0x40021000 + 0x58))
#define PWR_CR2       (*(volatile uint32_t*)(0x40007000 + 0x04))
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))

#define GPIOB  ((GPIO_t*)0x48000400)
#define GPIOG  ((GPIO_t*)0x48001800)
#define GPIOE   ((GPIO_t*)0x48001000)

#define DELAY_BETWEEN_DISPLAYING_DIGITS 1
#define DELAY_BETWEEN_CHANGING_NUMBERS 10000
#define JOY_DELAY (DELAY_BETWEEN_CHANGING_NUMBERS / 20)
#define CPU_CYCLES_PER_MS 150

#define NUM_LEN 4

#define TIM6 ((TIM6_t *)0x40001000)

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
void init_tim6(){
	RCC_APB1ENR1 |= (1 << 4);
	TIM6->PSC=3999;
	TIM6->ARR=1000;
	TIM6->CR1 |= 1;
}
void init_gpios(){
	RCC_APB1ENR1 |= (1 << 28);
	PWR_CR2 |= (1 << 9);

	RCC_AHB2ENR |= (1 << 1) | (1 << 4) | (1 << 6);

    GPIOB->MODER &= ~((3 << 4) | (3 << 6) | (3 << 8) | (3 << 10));
    GPIOB->MODER |= ((1 << 4) | (1 << 6) | (1 << 8) | (1 << 10));

    GPIOG->MODER &= ~((3 << 0) | (3<<2) |(3 << 4) | (3 << 6) | (3 << 8) | (3 << 10) | (3 << 12) | (3 << 18));
    GPIOG->MODER |= ((1 << 0) | (1<<2) |(1 << 4) | (1 << 6) | (1 << 8) | (1 << 10) | (1 << 12) | (1 << 18));

    GPIOE->MODER &= ~(3 << 30);

    GPIOE->PUPDR &= ~(3 << (30));
    GPIOE->PUPDR |=  (1 << (30));
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
void delay_ms(volatile uint32_t ms)
{
    for (uint64_t i = 0; i < ms * CPU_CYCLES_PER_MS; i++)
    {
        __asm("nop");
    }
}
void delay_ms_tim6(volatile uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        TIM6->CNT = 0;
        TIM6->SR &= (1<<0);
        while(!(TIM6->SR & 1));
    }
}
void display_number(int32_t number)
{
    static int8_t current_digit = 0;

    int8_t digits[NUM_LEN];

    digits[0] = number % 10;
    digits[1] = (number / 10) % 10;
    digits[2] = (number / 100) % 10;
    digits[3] = (number / 1000) % 10;

    GPIOB->ODR &= ~(
        (1 << 2) |
        (1 << 3) |
        (1 << 4) |
        (1 << 5)
    );

    GPIOG->ODR &= ~0x7F;

    GPIOG->ODR |= segment_codes[digits[current_digit]];

    GPIOB->ODR |= (1 << (5 - current_digit));

    current_digit++;

    if (current_digit >= NUM_LEN)
    {
        current_digit = 0;
    }
}

int main()
{
    init_tim6();
    init_gpios();

    int32_t counter = 0;
    int8_t direction = 1;
    uint64_t timer = 0;

    while (1)
    {

        if (timer!=0 && timer % DELAY_BETWEEN_CHANGING_NUMBERS == 0){
            counter+=direction;
        }
        if (counter > 9999)
        {
        	counter = 0;
        }
        else if(counter < 0){
        	counter = 9999;
        }
        if(timer % JOY_DELAY == 0){
        	if((GPIOE->IDR & (1 << 15))){
        		direction = 1;
        	}
        	else{
        		direction = -1;
        	}
        }

        delay_ms_tim6(DELAY_BETWEEN_DISPLAYING_DIGITS);
        display_number(counter);
        timer+=DELAY_BETWEEN_DISPLAYING_DIGITS;
    }

    return 0;
}
