
#ifndef RCC_H
#define RCC_H

#include <stdint.h>

typedef enum {
    RCC_OK = 0,
    RCC_Error = 1
} RCC_Status;

RCC_Status RCC_Config(uint32_t frequency);

uint32_t RCC_GetSystemClockFrequency(void);


#endif // RCC_H