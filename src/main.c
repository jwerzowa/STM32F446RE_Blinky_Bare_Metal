#include "../drivers/inc/rcc.h"
#include "../drivers/inc/gpio.h"
#include "../drivers/inc/systick.h"
#include "../drivers/inc/usart.h"

void delay(uint32_t count) {
    while(count--);
}


int main(void) {
    RCC_Config(180000000);
    SysTick_Init(180000000);

    USART_Config usart_config = {
        .USART_port = GPIOA,
        .TX_pin = 2,
        .RX_pin = 3,
        .bauderate = 115200,
        .alternate_function = 7
    };

    
    USART_init(USART2, &usart_config);
        
    

    while(1) {
        USART_transmit(USART2, (uint8_t*)"Hello\r\n", 7);
        delay(1000000); // tune this to whatever's a visible interval
    }
    
}