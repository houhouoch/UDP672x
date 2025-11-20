#ifndef _GPIO_DEVICE_H_
#define _GPIO_DEVICE_H_

#include "main.h"


typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t initFlag;
} GPIO_Def;

extern const GPIO_Def Power_ledPin_Lock;

void gpio_init(GPIO_Def gpio, uint32_t mode);

void gpio_set(GPIO_Def gpio, uint8_t value);

uint8_t gpio_get(GPIO_Def gpio);

void gpio_troggle(GPIO_Def gpio);
#endif
