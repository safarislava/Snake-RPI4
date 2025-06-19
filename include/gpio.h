#pragma once

#include "peripherals/gpio.h"

typedef enum _GpioFunc {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2
} GpioFunc;

typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_DOWN = 1,
    GPIO_PULL_UP = 2
} GpioPull;

void gpio_pin_set_func(u8 pinNumber, GpioFunc func);
void gpio_pin_enable(u8 pinNumber, GpioPull pull);
void gpio_digital_write(u32 pin);
void gpio_digital_clear(u32 pin);
u32 gpio_digital_read(u32 pin);
