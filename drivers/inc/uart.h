#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "gpio.h"

typedef struct {
    GPIO_TypeDef* UART_port;
    uint32_t CTS_pin;
    uint32_t RTS_pin;
    uint32_t TX_pin;
    uint32_t RX_pin;
    uint32_t CK_pin;
    uint32_t bauderate;
    uint8_t af;
} UART_Config;

typedef struct {
    volatile uint32_t USART_SR;
    volatile uint32_t USART_DR;
    volatile uint32_t USART_BRR;
    volatile uint32_t USART_CR1;
    volatile uint32_t USART_CR2;
    volatile uint32_t USART_CR3;
    volatile uint32_t USART_GTPR;
} UART_TypeDef;


void UART_init(UART_TypeDef* UARTx, UART_Config* config);
void UART_transmit(UART_TypeDef* UARTx, uint8_t* data, uint16_t size);
void UART_receive(UART_TypeDef* UARTx, uint8_t* data, uint16_t size);

#define

#endif // UART_H