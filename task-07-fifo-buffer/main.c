#include "lpuart.h"
#include "tim6.h"

void LPUART1_IRQHandler(){
	if(LPUART->ISR & (1 << 5)){
		char c = LPUART->RDR;
		if(c < '0' || c > '9'){
			LPUART_SendChar('.');
		}
		else{
			if(!is_fifo_full(&fifo)){
				fifo_put(&fifo, c);
				LPUART_SendChar(c);
			}
			else{
				LPUART_SendChar('x');
			}
		}
	}
}

int main()
{
    fifo_init(&fifo);
    LPUART_init();
    init_tim6();
    init_gpios();

    int32_t current_val = -1;

    while(1)
    {
        if(!is_fifo_empty(&fifo))
        {
            char c;
            fifo_get(&fifo, &c);

            current_val = c - '0';
        }

        if(current_val != -1){
        	display_number(current_val);
        	current_val = -1;
        }
    }
}
