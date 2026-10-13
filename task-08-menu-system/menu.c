#include "menu.h"
#include "lpuart.h"
#include "fifo.h"
#include "led.h"
#include "display.h"

#include <string.h>
#include <stdlib.h>

// struktura rejestrów GPIO dla dżojstika (port E)
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
} GPIO_TypeDef_Menu;

#define GPIOE_MENU ((GPIO_TypeDef_Menu *) 0x48001000)

struct FIFO my_fifo;

enum MenuState { MENU_MAIN, MENU_LED, MENU_7LED, MENU_JOY, MENU_LPUART };
static enum MenuState current_menu = MENU_MAIN;

static char cmd_buffer[32];
static uint8_t cmd_idx = 0;

void Menu_Init(void) {
    fifo_init(&my_fifo);
    LPUART_SendString("\r\nMain menu\r\n");
    LPUART_SendString("Wybierz opcje:\r\n"
            "LED\r\n"
            "7-LED\r\n"
            "Joy\r\n"
            "LPUART\r\n"
            "Pomoc\r\n"
            "> ");
}

void LPUART1_IRQHandler(void) {
    if (LPUART1->ISR & (1 << 5)) {
        char received = (char)(LPUART1->RDR & 0xFF);
        if (!is_fifo_full(&my_fifo)) {
            fifo_put(&my_fifo, received);
        }
    }
}

static void print_int(uint32_t val) {
    char buf[12];
    uint8_t i = 11;
    buf[i] = '\0';

    if (val == 0) buf[--i] = '0';
    while (val > 0) {
        buf[--i] = (val % 10) + '0';
        val /= 10;
    }
    LPUART_SendString(&buf[i]);
}

static uint8_t Get_LED_Index(char id) {
    if (id >= '0' && id <= '7') return id - '0';
    if (id == 'R' || id == 'r') return 8;
    if (id == 'G' || id == 'g') return 9;
    if (id == 'B' || id == 'b') return 10;
    return 255;
}

static void Print_Prompt(void) {
    switch(current_menu) {
        case MENU_MAIN:
            LPUART_SendString("Main menu\r\n");
            LPUART_SendString(
                "Wybierz opcje:\r\n"
                "LED\r\n"
                "7-LED\r\n"
                "Joy\r\n"
                "LPUART\r\n"
                "Pomoc\r\n"
                "> "
            );
            break;

        case MENU_LED:    LPUART_SendString("LED> "); break;
        case MENU_7LED:   LPUART_SendString("7-LED> "); break;
        case MENU_JOY:    LPUART_SendString("Joy> "); break;
        case MENU_LPUART: LPUART_SendString("LPUART> "); break;
    }
}

// ================= COMMAND EXECUTION =================
static void Execute_Command(char* cmd) {

    // ================= BACK COMMAND =================
    if (strcmp(cmd, "BACK") == 0) {
        current_menu = MENU_MAIN;
        Print_Prompt();
        return;
    }

    // ================= MAIN MENU =================
    if (current_menu == MENU_MAIN) {

        if (strcmp(cmd, "LED") == 0) {
            current_menu = MENU_LED;
        }
        else if (strcmp(cmd, "7-LED Display") == 0 ||
                 strcmp(cmd, "7-LED") == 0 ||
                 strcmp(cmd, "7LED") == 0 ||
                 strcmp(cmd, "7") == 0) {
            current_menu = MENU_7LED;
        }
        else if (strcmp(cmd, "Joy") == 0) {
            current_menu = MENU_JOY;
        }
        else if (strcmp(cmd, "LPUART") == 0) {
            current_menu = MENU_LPUART;
        }
        else if (strcmp(cmd, "Pomoc") == 0 || strcmp(cmd, "pom") == 0) {
            LPUART_SendString(
                "Dostepne: LED, 7LED, Joy, LPUART\r\n"
                "Powrot: BACK\r\n"
            );
        }
        else {
            LPUART_SendString("Nieznana komenda\r\n");
        }
    }

    // ================= LED MENU =================
    else if (current_menu == MENU_LED) {

        if (strncmp(cmd, "Set ", 4) == 0)
            LED_Control(Get_LED_Index(cmd[4]), 1);

        else if (strncmp(cmd, "Clear ", 6) == 0)
            LED_Control(Get_LED_Index(cmd[6]), 0);

        else if (strncmp(cmd, "Toggle ", 7) == 0)
            LED_Control(Get_LED_Index(cmd[7]), 2);

        else if (strncmp(cmd, "Blink ", 6) == 0)
            LED_StartBlink(Get_LED_Index(cmd[6]));

        else if (strncmp(cmd, "Status ", 7) == 0) {
            uint8_t idx = Get_LED_Index(cmd[7]);
            LPUART_SendString("Status: ");
            LPUART_SendChar(LED_Status(idx) ? '1' : '0');
            LPUART_SendString("\r\n");
        }
        else {
            LPUART_SendString("Set/Clear/Toggle/Blink/Status <id>\r\n");
        }
    }

    // ================= 7-SEG MENU =================
    else if (current_menu == MENU_7LED) {

        if (strncmp(cmd, "Display ", 8) == 0) {
            Display_SetValue((uint32_t)strtoul(&cmd[8], NULL, 10));
        }
        else if (strcmp(cmd, "Read") == 0) {
            LPUART_SendString("Value: ");
            print_int(Display_GetValue());
            LPUART_SendString("\r\n");
        }
        else {
            LPUART_SendString("Display <val>, Read\r\n");
        }
    }

    // ================= JOY MENU =================
    else if (current_menu == MENU_JOY) {

        if (strncmp(cmd, "Read ", 5) == 0) {
            char id = cmd[5];

            LPUART_SendString("Joy ");
            LPUART_SendChar(id);
            LPUART_SendString(": ");

            if (id == 'R') print_int((GPIOE_MENU->IDR & (1 << 0)) ? 0 : 1);
            else if (id == 'L') print_int((GPIOE_MENU->IDR & (1 << 1)) ? 0 : 1);
            else if (id == 'D') print_int((GPIOE_MENU->IDR & (1 << 2)) ? 0 : 1);
            else if (id == 'U') print_int((GPIOE_MENU->IDR & (1 << 3)) ? 0 : 1);
            else if (id == 'C') print_int((GPIOE_MENU->IDR & (1 << 15)) ? 0 : 1);

            LPUART_SendString("\r\n");
        }
        else {
            LPUART_SendString("Read <L,R,U,D,C>\r\n");
        }
    }

    // ================= LPUART MENU =================
    else if (current_menu == MENU_LPUART) {

        if (strcmp(cmd, "Status") == 0) {

            uint32_t brr = LPUART1->BRR;
            uint32_t baudrate = (256 * 4000000) / brr;

            LPUART_SendString("Baudrate: ");
            print_int(baudrate);
            LPUART_SendString("\r\n");

            uint32_t cr1 = LPUART1->CR1;
            uint32_t cr2 = LPUART1->CR2;

            uint8_t data_bits = 8;
            if (cr1 & (1 << 28)) data_bits = 7;
            else if (cr1 & (1 << 12)) data_bits = 9;

            char parity = 'N';
            if (cr1 & (1 << 10)) {
                parity = (cr1 & (1 << 9)) ? 'O' : 'E';
            }

            uint8_t stop_val = (cr2 >> 12) & 0x03;
            uint8_t stop_bits = (stop_val == 2) ? 2 : 1;

            LPUART_SendString("Frame: ");
            print_int(data_bits);
            LPUART_SendChar(parity);
            print_int(stop_bits);
            LPUART_SendString("\r\n");
        }
        else {
            LPUART_SendString("Status\r\n");
        }
    }

    Print_Prompt();
}

// ================= MAIN LOOP PROCESS =================
void Menu_Process(void) {
    if (!is_fifo_empty(&my_fifo)) {

        char c;
        fifo_get(&my_fifo, &c);

        if (c == '\r' || c == '\n') {

            LPUART_SendString("\r\n");
            cmd_buffer[cmd_idx] = '\0';

            if (cmd_idx > 0)
                Execute_Command(cmd_buffer);
            else
                Print_Prompt();

            cmd_idx = 0;
        }
        else if (c == '\b' || c == 0x7F) {
            if (cmd_idx > 0) {
                cmd_idx--;
                LPUART_SendString("\b \b");
            }
        }
        else {
            if (cmd_idx < sizeof(cmd_buffer) - 1) {
                cmd_buffer[cmd_idx++] = c;
                LPUART_SendChar(c);
            }
        }
    }
}
