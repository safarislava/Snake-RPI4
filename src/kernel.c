#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "led.h"
#include "keyboard.h"

void putc(void *p, char c) {
    if (c == '\n') {
        uart_send('\r');
    }

    uart_send(c);
}

u32 get_el();

void kernel_main() {
    uart_init();
    init_printf(0, putc);
    printf("\nRasperry PI Bare Metal OS Initializing...\n");

    irq_init_vectors();
    enable_interrupt_controller();
    irq_enable();
    led_init();
    keyboard_init();
    timer_init();

    printf("\tBoard: Raspberry PI 4\n");

    printf("\nException Level: %d\n", get_el());

    while(1) {
        continue;
        // char symbol = scan_keyboard();
        // if (symbol != 'Z') {
            // printf("Symbol: %c\n", symbol);
        // }
    }
}
