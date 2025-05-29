#include <stdint.h>
#include "interrupt.h"

volatile uint32_t* IRQ_PENDING_0 = (volatile uint32_t*)(IRQ_BASE + 0x204);
volatile uint32_t* IRQ_ENABLE_0  = (volatile uint32_t*)(IRQ_BASE + 0x214);

void irq_handler(void) {
    led_on();
    if (*IRQ_PENDING_0 & (1 << 17)) {
        handle_gpio_irq();
        *IRQ_PENDING_0 = (1 << 17);
    }
}

void handle_gpio_irq(void) {
    uint32_t events = GPIO_REGS->event_detect.data[0] & GPIO_MASK;
    
    if (events) {
        if (events & (1 << 12)) { /* GPIO12 */ }
        if (events & (1 << 16)) { /* GPIO16 */ }
        if (events & (1 << 20)) { /* GPIO20 */ }
        if (events & (1 << 21)) { /* GPIO21 */ }
        
        GPIO_REGS->event_detect.data[0] = events;
    }
}

void enable_irq(void) {
    *IRQ_ENABLE_0 |= (1 << 17);
    asm volatile("msr daifclr, #2");
}

void disable_irq(void) {
    *IRQ_ENABLE_0 &= ~(1 << 17);
    asm volatile("msr daifset, #2");
}

void setup_gpio_interrupts(void) {    
    GPIO_REGS->event_detect.data[0] = GPIO_MASK;

    GPIO_REGS->falling_edge_detect.data[0] = GPIO_MASK;  
    
    *IRQ_ENABLE_0 |= (1 << 17);
}