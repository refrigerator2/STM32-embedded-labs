
#include <stdint.h>
#define RCC_APB1ENR1  (*(volatile uint32_t*)(0x40021000 + 0x58))
#define PWR_CR2       (*(volatile uint32_t*)(0x40007000 + 0x04))
#define RCC_AHB2ENR   (*(volatile uint32_t*)(0x40021000 + 0x4C))

#define GPIOB_MODER   (*(volatile uint32_t*)(0x48000400))
#define GPIOG_MODER   (*(volatile uint32_t*)(0x48001800))

#define GPIOB_ODR (*(volatile uint32_t*)(0x48000400 + 0x14))
#define GPIOG_ODR (*(volatile uint32_t*)(0x48001800 + 0x14))

#define GPIOE_MODER   (*(volatile uint32_t*)(0x48001000 + 0x00))
#define GPIOE_PUPDR   (*(volatile uint32_t*)(0x48001000 + 0x0C))
#define GPIOE_IDR     (*(volatile uint32_t*)(0x48001000 + 0x10))

#define DELAY_BETWEEN_DISPLAYING_DIGITS 1
#define DELAY_BETWEEN_CHANGING_NUMBERS 1000
#define JOY_DELAY (DELAY_BETWEEN_CHANGING_NUMBERS / 20)
#define NUM_LEN 4
#define CPU_CYCLES_PER_MS 300

void init_gpios(){
	RCC_APB1ENR1 |= (1 << 28);
	PWR_CR2 |= (1 << 9);

	RCC_AHB2ENR |= (1 << 1) | (1 << 4) | (1 << 6);

    GPIOB_MODER &= ~((3 << 4) | (3 << 6) | (3 << 8) | (3 << 10));
    GPIOB_MODER |= ((1 << 4) | (1 << 6) | (1 << 8) | (1 << 10));

    GPIOG_MODER &= ~((3 << 0) | (3<<2) |(3 << 4) | (3 << 6) | (3 << 8) | (3 << 10) | (3 << 12) | (3 << 18));
    GPIOG_MODER |= ((1 << 0) | (1<<2) |(1 << 4) | (1 << 6) | (1 << 8) | (1 << 10) | (1 << 12) | (1 << 18));

    GPIOE_MODER &= ~(3 << 30);

    GPIOE_PUPDR &= ~(3 << (30));
    GPIOE_PUPDR |=  (1 << (30));
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

void display_number(int32_t number)
{
    static int8_t current_digit = 0;

    int8_t digits[NUM_LEN];

    digits[0] = number % 10;
    digits[1] = (number / 10) % 10;
    digits[2] = (number / 100) % 10;
    digits[3] = (number / 1000) % 10;

    GPIOB_ODR &= ~(
        (1 << 2) |
        (1 << 3) |
        (1 << 4) |
        (1 << 5)
    );

    GPIOG_ODR &= ~0x7F;

    GPIOG_ODR |= segment_codes[digits[current_digit]];

    GPIOB_ODR |= (1 << (5 - current_digit));

    current_digit++;

    if (current_digit >= 4)
    {
        current_digit = 0;
    }
}

int main()
{
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
        	if((GPIOE_IDR & (1 << 15))){
        		direction = 1;
        	}
        	else{
        		direction = -1;
        	}
        }

        delay_ms(DELAY_BETWEEN_DISPLAYING_DIGITS);
        display_number(counter);
        timer+=DELAY_BETWEEN_DISPLAYING_DIGITS;
    }

    return 0;
}
