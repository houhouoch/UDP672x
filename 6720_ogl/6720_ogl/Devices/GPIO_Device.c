#include "GPIO_Device.h"

#ifdef HAOYI_VER
const GPIO_Def Power_ledPin_Lock = {
    .port = GPIOE,
    .pin = GPIO_PIN_0,
};
#else
const GPIO_Def Power_ledPin_Lock = {
    .port = LED_LOCK_GPIO_Port,
    .pin = LED_LOCK_Pin,
};
#endif

void gpio_init(GPIO_Def gpio, uint32_t mode)
{
    if(gpio.initFlag == 0) {
        gpio.initFlag = 1;
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = gpio.pin;
        GPIO_InitStruct.Mode = mode;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(gpio.port, &GPIO_InitStruct);
    }
}

void gpio_set(GPIO_Def gpio, uint8_t value)
{
    //    HAL_GPIO_WritePin(gpio.port, gpio.pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    if(gpio.port == NULL) { return ; }
    if(value == 0) {
        gpio.port->ODR &= ~(gpio.pin);
    } else {
        gpio.port->ODR |= (gpio.pin);
    }
}


uint8_t gpio_get(GPIO_Def gpio)
{
    if(gpio.port == NULL) { return 0; }
    //    return HAL_GPIO_ReadPin(gpio.port, gpio.pin);
    return ((gpio.port->IDR & (gpio.pin)) != 0);
}

void gpio_troggle(GPIO_Def gpio)
{
    if(gpio.port == NULL) { return ; }
    //    HAL_GPIO_TogglePin(gpio.port, gpio.pin);
    gpio.port->ODR ^= (gpio.pin);
}
