#include "gpio.h"
#include "utils.h"

void gpio_pin_set_func(u8 pin, GpioFunc func) {
    u8 bitStart = (pin * 3) % 30;
    u8 reg = pin / 10;

    u32 selector = REGS_GPIO->func_select[reg];
    selector &= ~(7 << bitStart);
    selector |= (func << bitStart);

    REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pin, GpioPull pull) {
    REGS_GPIO->pupd_enable = pull;
    delay(150);
    REGS_GPIO->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
    delay(150);
    REGS_GPIO->pupd_enable = 0;
    REGS_GPIO->pupd_enable_clocks[pin / 32] = 0;
}

void gpio_digital_write(u32 pin)
{
    REGS_GPIO->output_set.data[pin / 32] = (1 << (pin % 32));
}

void gpio_digital_clear(u32 pin)
{
    REGS_GPIO->output_clear.data[pin / 32] = (1 << (pin % 32));
}

u32 gpio_digital_read(u32 pin)
{
    return (REGS_GPIO->level.data[pin / 32] >> (pin % 32)) & 1;
}

void gpio_enable_falling_edge_detect(u32 pin) {
    REGS_GPIO->fe_detect_enable.data[pin / 32] |= (1 << (pin % 32));
}

void gpio_enable_rising_edge_detect(u32 pin) {
    REGS_GPIO->re_detect_enable.data[pin / 32] |= (1 << (pin % 32));
}

void gpio_disable_falling_edge_detect(u32 pin) {
    REGS_GPIO->fe_detect_enable.data[pin / 32] &= ~(1 << (pin % 32));
}

void gpio_disable_rising_edge_detect(u32 pin) {
    REGS_GPIO->re_detect_enable.data[pin / 32] &= ~(1 << (pin % 32));
}

void gpio_clear_event_detect(u32 pin) {
    REGS_GPIO->ev_detect_status.data[pin / 32] = (1 << (pin % 32));  // Write 1 to clear
}

u32 gpio_get_event_detect_status(u32 pin) {
    return (REGS_GPIO->ev_detect_status.data[pin / 32] >> (pin % 32)) & 1;
}