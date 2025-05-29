#pragma once

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define PERIPHERAL_BASE 0xFE000000U
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000U)

struct GpioPinData {
    volatile uint32_t reserved;
    volatile uint32_t data[2];
};

struct GpioRegs {
    volatile uint32_t fun_select[6];
    struct GpioPinData output_set;
    struct GpioPinData output_clear;
    struct GpioPinData level;
    struct GpioPinData event_detect;
    struct GpioPinData rising_edge_detect;
    struct GpioPinData falling_edge_detect;
    struct GpioPinData high_detect;
    struct GpioPinData low_detect;
    struct GpioPinData async_rising_edge_detect;
    struct GpioPinData async_falling_edge_detect;
    volatile uint32_t reserved;
    volatile uint32_t pupd_enable;
    volatile uint16_t pupd_enable_clock[2];
};

#define GPIO_REGS ((volatile struct GpioRegs *)(GPIO_BASE))

typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2
} GpioFunc;

typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_DOWN = 1,
    GPIO_PULL_UP = 2
} GpioPull;

void gpio_pin_enable(uint32_t pin, GpioPull pull);
void gpio_pin_set_func(uint32_t pin, GpioFunc func);
void gpio_init(void);
void gpio_digital_write(uint32_t pin);
void gpio_digital_clear(uint32_t pin);
uint32_t gpio_digital_read(uint32_t pin);
void init_interrupts(void);
void led_on(void);
void led_off(void);
void delay(unsigned int cycles);

#endif