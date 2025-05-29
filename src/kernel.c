#include "interrupt.h"
#include "ssd1306.h"

void kernel_main(void);

void kernel_main(void) { 
    gpio_init();
    ssd1306_init();
    setup_gpio_interrupts();
    enable_irq();
    
    ssd1306_clear();
    ssd1306_draw_string(0, 0, "Hello, World!");
    ssd1306_update();

    while(1){
        delay(100000);
    }
}