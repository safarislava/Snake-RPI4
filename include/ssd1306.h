#pragma once

#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stddef.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_PAGES (SSD1306_HEIGHT / 8)

#define SSD1306_I2C_ADDR 0x3C

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_update(void);
void ssd1306_draw_pixel(int x, int y, int color);
void ssd1306_draw_big_pixel(int x, int y, int color, int size);
void ssd1306_draw_char(int x, int y, char ch);
void ssd1306_fill(void);
void ssd1306_draw_string(int x, int y, char *str);

#endif