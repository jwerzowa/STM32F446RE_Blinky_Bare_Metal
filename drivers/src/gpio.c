

//Instantiate all the addresses, make a structure for each GPIO port, and then make a pointer to each structure.

#include "../inc/gpio.h"
#include "../inc/rcc.h"
#include <stdint.h>

void GPIO_Init(GPIO_TypeDef* port, GPIO_PinConfig* config) {
    
    //Enable the clock for the GPIO port, set the appropriate bit based on port address, given the offsets are consistently 0x400 apart, we can calculate the bit position by subtracting the base address of GPIOA from the port address and dividing by 0x400.
    RCC->RCC_AHB1ENR |= (1 << ((uint32_t)port - (uint32_t)GPIOA) / 0x400);
    
    //force the CPU to wait for the bus to complete the previous write before continuing
    volatile uint32_t dummy = RCC->RCC_AHB1ENR;
    (void)dummy;


    //Set the mode, output type, speed, and pull-up or pull-down configuration for the specified pin.
    port->MODER &= ~(3 << config->pin *2);
    port->MODER |= (config->mode << config->pin *2);

    port->OTYPER &= ~(1 << config->pin);
    port->OTYPER |= (config->output_type << config->pin);

    port->OSPEEDR &= ~(3 << config->pin *2);
    port->OSPEEDR |= (config->speed << config->pin *2);

    port->PUPDR &= ~(3 << config->pin *2);
    port->PUPDR |= (config->pull << config->pin *2);

}