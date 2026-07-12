#include "../inc/usart.h"
#include "../inc/rcc.h"
#include "../inc/gpio.h"

void UART_init(USART_TypeDef* UARTx, USART_Config* config) {
    
    if(UARTx == USART1) {
        RCC->RCC_APB2ENR |= (1 << 4); // Enable clock for USART1
    } else if(UARTx == USART2) {
        RCC->RCC_APB1ENR |= (1 << 17); // Enable clock for USART2
    } else if(UARTx == USART3) {
        RCC->RCC_APB1ENR |= (1 << 18); // Enable clock for USART3
    } else if(UARTx == UART4) {
        RCC->RCC_APB1ENR |= (1 << 19); // Enable clock for UART4
    } else if(UARTx == UART5) {
        RCC->RCC_APB1ENR |= (1 << 20); // Enable clock for UART5
    } else if(UARTx == USART6) {
        RCC->RCC_APB2ENR |= (1 << 5); // Enable clock for USART6
    }

    RCC->RCC_AHB1ENR |= (1 << ((uint32_t)config->USART_port - (uint32_t)GPIOA) / 0x400); // Enable clock for GPIO port

    GPIO_PinConfig tx_config = {
        .pin = config->TX_pin,
        .mode = GPIO_MODE_ALTERNATE,
        .output_type = GPIO_OUTPUT_PUSH_PULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_PULL_NONE,
        .alternate_function = config->alternate_function
    };

    GPIO_PinConfig rx_config = {
        .pin = config->RX_pin,
        .mode = GPIO_MODE_ALTERNATE,
        .output_type = GPIO_OUTPUT_PUSH_PULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_PULL_UP,
        .alternate_function = config->alternate_function
    };

    GPIO_Init(config->USART_port, &tx_config);
    GPIO_Init(config->USART_port, &rx_config);
    


    // 1. enable clock for UARTx's bus — which register, which bit?
    // 2. enable clock for config->UART_port's GPIO — which register, which bit?
    // 3. build a GPIO_PinConfig for TX, call GPIO_Init
    // 4. build a GPIO_PinConfig for RX, call GPIO_Init
    // 5. compute BRR from config->bauderate
    // 6. set CR1 bits: UE, TE, RE
    // 7. ...
}