#include <stdint.h>
#include "interrupt.h"
#include "keyboard.h"

volatile uint32_t* IRQ_PENDING_1 = (volatile uint32_t*)(IRQ_BASE + 0x204);
volatile uint32_t* IRQ_ENABLE_1 = (volatile uint32_t*)(IRQ_BASE + 0x214);

char last_char = '\0';

void irq_handler(void) {
    led_on();
    if (*IRQ_PENDING_1 & (1 << 17)) {
        last_char = scan_keyboard();
        *IRQ_PENDING_1 = (1 << 17);
    }
}

char get_last_char(void) {
    return last_char;
}

void enable_irq(void) {
    *IRQ_ENABLE_1 |= (1 << 17);
    asm volatile("msr daifclr, #2");
}

void disable_irq(void) {
    *IRQ_ENABLE_1 &= ~(1 << 17);
    asm volatile("msr daifset, #2");
}

void interrupt_init(void) {    
    keyboard_init();
    GPIO_REGS->event_detect.data[0] = GPIO_MASK;
    GPIO_REGS->falling_edge_detect.data[0] = GPIO_MASK;  
}