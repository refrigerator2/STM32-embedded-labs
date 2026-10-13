#include "led.h"
#include "hardware.h"

static uint8_t led_blink_counters[11] = {0};
static uint32_t led_blink_timers[11] = {0};

static void Get_LED_PortPin(uint8_t idx, GPIO_TypeDef **port, uint32_t *pin) {
    switch(idx) {
        case 0:  *port = GPIOC; *pin = 6;  break;
        case 1:  *port = GPIOC; *pin = 7;  break;
        case 2:  *port = GPIOC; *pin = 8;  break;
        case 3:  *port = GPIOC; *pin = 9;  break;
        case 4:  *port = GPIOE; *pin = 4;  break;
        case 5:  *port = GPIOD; *pin = 3;  break;
        case 6:  *port = GPIOE; *pin = 5;  break;
        case 7:  *port = GPIOE; *pin = 6;  break;
        case 8:  *port = GPIOD; *pin = 13; break; // r
        case 9:  *port = GPIOB; *pin = 8;  break; // g
        case 10: *port = GPIOD; *pin = 12; break; // b
        default: *port = 0;     *pin = 0;  break;
    }
}

void LED_Control(uint8_t idx, uint8_t action) { 
    GPIO_TypeDef *port; uint32_t pin;
    Get_LED_PortPin(idx, &port, &pin);
    if (!port) return;
    
    if (action == 1) port->BSRR = (1 << pin);
    else if (action == 0) port->BSRR = (1 << (pin + 16));
    else if (action == 2) {
        if (port->ODR & (1 << pin)) port->BSRR = (1 << (pin + 16));
        else port->BSRR = (1 << pin);
    }
}

uint8_t LED_Status(uint8_t idx) {
    GPIO_TypeDef *port; uint32_t pin;
    Get_LED_PortPin(idx, &port, &pin);
    if (!port) return 0;

    return (port->ODR & (1 << pin)) ? 1 : 0; // czytanie wyjścia
}

void LED_StartBlink(uint8_t idx) {
    if(idx < 11) {
        led_blink_counters[idx] = 2*5; // 5 zapaleń, 5 zgaszeń
        led_blink_timers[idx] = sys_tick; // pobranie obecnego czasu
    }
}

void LED_Process(void) {
    for (uint8_t i = 0; i < 11; i++) {
        if (led_blink_counters[i] > 0) {
            if (sys_tick - led_blink_timers[i] >= 200) { // zmiana stanu co 200ms
                LED_Control(i, 2); 
                led_blink_timers[i] = sys_tick;
                led_blink_counters[i]--;
            }
        }
    }
}
