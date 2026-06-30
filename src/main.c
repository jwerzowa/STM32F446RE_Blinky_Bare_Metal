
#include <stdint.h>


#define RCC_AHB1ENR  (*(volatile uint32_t*) (0x40023830))
#define GPIOA_MODER  (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR    (*(volatile uint32_t*)0x40020014)

void delay(int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 1000; j++) {
            // Do nothing, just waste time
        }
    }
}

int main() {
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0);

    // Set PA5 as output (01)
    GPIOA_MODER &= ~(0x3 << (5 * 2)); // Clear mode bits for PA5
    GPIOA_MODER |= (0x1 << (5 * 2));  // Set mode to output

    while (1) {
        // Toggle PA5
        GPIOA_ODR ^= (1 << 5);
        delay(1000); // Delay for a while
    }

    return 0;
}