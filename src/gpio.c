#include "gpio.h"
#include <stdint.h>

void gpio_init(void) {
    gpio_pin_enable(17);
    gpio_pin_set_func(17, GPIO_OUTPUT);
    gpio_pin_enable(2);
    gpio_pin_set_func(2, GPIO_ALT0);
    gpio_pin_enable(3);
    gpio_pin_set_func(3, GPIO_ALT0);
}

void gpio_pin_enable(uint32_t pin) {
    uint32_t bit = pin % 32; 
    uint32_t regIndex = pin / 32;
    
    GPIO_REGS->pupd_enable = 0; 
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

void led_on(void) {
    gpio_digital_write(17);
}

void led_off(void) {
    gpio_digital_clear(17);
}

void delay(unsigned int cycles) {
    while(cycles--) asm volatile("nop");
}