#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void Display_Init(void);
void Display_SetValue(uint32_t val);
uint32_t Display_GetValue(void);
void Display_Process(void);

#endif
