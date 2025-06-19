#include "led.h"
#include "gpio.h"
#include "utils.h"

void led_init(void) {
    gpio_pin_enable(17, GPIO_PULL_NONE);
    gpio_pin_set_func(17, GPIO_OUTPUT);
}

void led_on(void)
{
    gpio_digital_write(17);
}

void led_off(void)
{
    gpio_digital_clear(17);
}