#pragma once

void keyboard_init(void);
void enable_rows(void);
void disable_rows(void);
char scan_keyboard(void);
void handle_keyboard_irq(void);