#include "gpio.h"
#include <stdint.h>

void gpio_init(void) {
    // LED
    gpio_pin_enable(17, GPIO_PULL_NONE);
    gpio_pin_set_func(17, GPIO_OUTPUT);

    // I2C
    gpio_pin_enable(2, GPIO_PULL_NONE);
    gpio_pin_set_func(2, GPIO_ALT0);
    gpio_pin_enable(3, GPIO_PULL_NONE);
    gpio_pin_set_func(3, GPIO_ALT0);

    const uint32_t rows[] = {6, 13, 19, 26};
    for (int i = 0; i < 4; i++) {
        gpio_pin_enable(rows[i], GPIO_PULL_NONE);
        gpio_pin_set_func(rows[i], GPIO_OUTPUT);
        gpio_digital_write(rows[i]); // Изначально строки неактивны
    }

    const uint32_t cols[] = {12, 16, 20, 21};
    for (int i = 0; i < 4; i++) {
        gpio_pin_enable(cols[i], GPIO_PULL_UP);
        gpio_pin_set_func(cols[i], GPIO_INPUT);
    }
}

void gpio_pin_enable(uint32_t pin, GpioPull pull) {
    uint32_t bit = pin % 32; 
    uint32_t regIndex = pin / 32;
    
    GPIO_REGS->pupd_enable = pull; 
    delay(150);
    GPIO_REGS->pupd_enable_clock[regIndex] |= (1 << bit);
    delay(150);
    GPIO_REGS->pupd_enable = 0; 
    GPIO_REGS->pupd_enable_clock[regIndex] = 0; 
}

void gpio_pin_set_func(uint32_t pin, GpioFunc func) {
    uint32_t bitStart = (pin * 3) % 30; 
    uint32_t regIndex = pin / 10;
    
    uint32_t selector = GPIO_REGS->fun_select[regIndex];
    selector &= ~(7 << bitStart);
    selector |= (func << bitStart);
    GPIO_REGS->fun_select[regIndex] = selector;
}

void gpio_digital_write(uint32_t pin) {
    GPIO_REGS->output_set.data[pin / 32] = (1 << (pin % 32));
}

void gpio_digital_clear(uint32_t pin) {
    GPIO_REGS->output_clear.data[pin / 32] = (1 << (pin % 32));
}

uint32_t gpio_digital_read(uint32_t pin) {
    uint32_t regIndex = pin / 32;
    uint32_t bit = pin % 32;
    return (GPIO_REGS->level.data[regIndex] >> bit) & 1;
}

void led_on(void) {
    gpio_digital_write(17);
}

void led_off(void) {
    gpio_digital_clear(17);
}

void delay(unsigned int cycles) {
    while(cycles--) asm volatile("nop");
}