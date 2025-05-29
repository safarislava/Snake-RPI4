#include <stdint.h>
#include "gpio.h"

const uint32_t rows[] = {6, 13, 19, 26};
const uint32_t cols[] = {12, 16, 20, 21};
const char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void keyboard_init(void) {
    for (int i = 0; i < 4; i++) {
        gpio_pin_enable(rows[i], GPIO_PULL_NONE);
        gpio_pin_set_func(rows[i], GPIO_OUTPUT);
    }
    enable_rows();

    for (int i = 0; i < 4; i++) {
        gpio_pin_enable(cols[i], GPIO_PULL_UP);
        gpio_pin_set_func(cols[i], GPIO_INPUT);
    }
}

void enable_rows(void) {
    for (int i = 0; i < 4; i++) {
        gpio_digital_write(rows[i]); 
    }
}

void disable_rows(void) {
    for (int i = 0; i < 4; i++) {
        gpio_digital_clear(rows[i]); 
    }
}

char scan_keyboard(void) {
    enable_rows();
    for (int col = 0; col < 4; col++) {
        uint32_t state = gpio_digital_read(cols[col]); 
        if (state == 0) continue;

        disable_rows();
        for (int row = 0; row < 4; row++) {
            gpio_digital_write(rows[row]); 
            if (gpio_digital_read(cols[col]) == 1) {
                char key = keymap[row][col];
                enable_rows();
                return key;
            }
            gpio_digital_clear(rows[row]); 
        }
    }

    return '\0';
}