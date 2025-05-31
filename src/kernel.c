#include "interrupt.h"
#include "ssd1306.h"
#include "gpio.h"

void kernel_main(void) { 
    gpio_init();
    ssd1306_init();
    interrupt_init();
    enable_irq();

    while (1) {
        ssd1306_clear();
        ssd1306_draw_char(0, 0, get_last_char());
        ssd1306_update();

        delay(5000);
    }

    // while (1) {
    //     char pressed_key = scan_keyboard();
    //     if (pressed_key != '\0') {
    //         ssd1306_clear();
    //         ssd1306_draw_char(0, 0, pressed_key);
    //     } 

    //     ssd1306_update();
    //     delay(5000);
    // }
}