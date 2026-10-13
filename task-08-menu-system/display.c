#include "display.h"
#include "hardware.h"

static uint32_t display_value = 0;

const uint32_t segment_codes[11] = {
    0x3F, 0x06, 0x5B, 0x4F,
    0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x00   // optional blank, not used now
};

void Display_Init(void)
{
    display_value = 0;
}

void Display_SetValue(uint32_t val)
{
    display_value = val;
}

uint32_t Display_GetValue(void)
{
    return display_value;
}

void Display_Process(void)
{
    static uint32_t last_disp_time = 0;
    static uint8_t curr_dig = 0;

    if (sys_tick - last_disp_time >= 1)
    {
        last_disp_time = sys_tick;

        // disable all digits
        GPIOB->ODR &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
        GPIOG->ODR &= ~0x7F;

        uint8_t val;

        switch (curr_dig)
        {
            case 0:
                val = (display_value / 1000) % 10;
                break;

            case 1:
                val = (display_value / 100) % 10;
                break;

            case 2:
                val = (display_value / 10) % 10;
                break;

            case 3:
                val = display_value % 10;
                break;
        }

        // show digit
        GPIOG->ODR |= segment_codes[val];
        GPIOB->ODR |= (1 << (2 + curr_dig));

        curr_dig = (curr_dig + 1) & 0x03;
    }
}