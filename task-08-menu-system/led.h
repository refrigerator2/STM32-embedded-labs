#ifndef LED_H
#define LED_H

#include <stdint.h>

void LED_Control(uint8_t idx, uint8_t action);
uint8_t LED_Status(uint8_t idx);
void LED_StartBlink(uint8_t idx);
void LED_Process(void);

#endif
