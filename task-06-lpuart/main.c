#include "lpuart.h"

unsigned char swap_case(unsigned char c)
{
    if (c >= 'a' && c <= 'z')
        return c - GAP_BETWEEN_CAPITALS_AND_ORDINARY_IN_ASCII;
    else if (c >= 'A' && c <= 'Z')
        return c + GAP_BETWEEN_CAPITALS_AND_ORDINARY_IN_ASCII;

    return c;
}

int main()
{
    LPUART_init();

    unsigned char *test1 = (unsigned char *)"\r\nHello world STM32 LPUART\r\n";
    LPUART_SendString(test1);

    unsigned char *test2 =
        (unsigned char *)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n";

    for (uint32_t i = 0; test2[i] != '\0'; i++)
    {
        LPUART_SendChar(test2[i]);
    }

    unsigned char received_char;
    unsigned char processed_char;

    while (1)
    {
        LPUART_ReceiveChar(&received_char);

        if (received_char == '\r' || received_char == '\n')
        {
            unsigned char nl[3] = "\r\n";
            LPUART_SendString(nl);
        }
        else
        {
        	LPUART_SendChar(received_char);
            processed_char = swap_case(received_char);
            LPUART_SendChar(processed_char);
        }
    }
}
