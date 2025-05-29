#pragma once
#include "gpio.h"

#ifndef INTERRUPT_H
#define INTERRUPT_H

#define IRQ_BASE (PERIPHERAL_BASE + 0xB000)

#define GPIO_MASK ((1 << 12) | (1 << 16) | (1 << 20) | (1 << 21))

void irq_handler(void);
void enable_irq(void);
void disable_irq(void);
void setup_gpio_interrupts(void);
void handle_gpio_irq(void);

#endif