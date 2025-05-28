#include "gpio.h"
#include "ssd1306.h"

void kernel_main(void);
void reset_handler(void);
void irq_handler(void);

// __attribute__((section(".vectors")))
// void (* const vectors[])(void) = {
//     (void (*)(void))0x20000000, // Stack pointer
//     reset_handler,              // Reset handler
//     0, 0, 0, 0, 0, 0,           // Reserved
//     irq_handler                 // IRQ handler
// };

void reset_handler(void) {
    // asm volatile("msr DAIFClr, #2");
    
    kernel_main();
}

void kernel_main(void) {  
    gpio_init();
    ssd1306_init();

    ssd1306_clear();
    ssd1306_draw_string(0, 0, "Hello, World!");
    ssd1306_update();

    while(1){
        delay(100000);
    }
}