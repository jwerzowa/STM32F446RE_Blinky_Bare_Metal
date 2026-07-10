#include "../drivers/inc/rcc.h"
#include "../drivers/inc/gpio.h"

void delay(uint32_t count) {
    while(count--);
}


int main(void) {
    RCC_Config(180000000);
    SysTick_Init(180000000);

    GPIO_PinConfig led = {
        .pin = 5,
        .mode = GPIO_MODE_OUTPUT,
        .output_type = GPIO_OUTPUT_PUSH_PULL,
        .speed = GPIO_SPEED_LOW,
        .pull = GPIO_PULL_NONE
    };

    GPIO_Init(GPIOA, &led);

    while (1) {
        GPIO_Toggle(GPIOA, 5);
        delay_ms(500);
    }
}