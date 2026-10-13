#include "hardware.h"
#include "lpuart.h"
#include "fifo.h"
#include "led.h"
#include "display.h"
#include "menu.h"


void TIM6_DACUNDER_IRQHandler(void) {
    if (TIM6->SR & (1 << 0)) {
        TIM6->SR &= ~(1 << 0);
        sys_tick++;
    }
}

int main(void) {
    Hardware_Init();
    LPUART_init();
    Menu_Init();
    Display_Init();

    while (1) {
        Menu_Process();
        LED_Process();
        Display_Process();
    }
}
