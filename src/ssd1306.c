#include "ssd1306.h"
#include "i2c.h"
#include "ssd1306_font.h"
#include <string.h>

static uint8_t framebuffer[SSD1306_WIDTH * SSD1306_PAGES];

static uint8_t i2c_payload_buffer[SSD1306_WIDTH + 1];

static void ssd1306_write_cmd(uint8_t cmd)
{
    i2c_payload_buffer[0] = 0x00;
    i2c_payload_buffer[1] = cmd;
    i2c_write(i2c_payload_buffer, 2);
}

static void ssd1306_write_data(const uint8_t *data, size_t len)
{
    if (len == 0 || len > SSD1306_WIDTH)
        return;

    i2c_payload_buffer[0] = 0x40;
    for (size_t i = 0; i < len; i++)
    {
        i2c_payload_buffer[i + 1] = data[i];
    }

    i2c_write(i2c_payload_buffer, len + 1);
}

void ssd1306_init(void)
{
    i2c_init();

    ssd1306_write_cmd(0xAE); // Display OFF
    ssd1306_write_cmd(0xD5); // Set Display Clock Divide
    ssd1306_write_cmd(0x80); // Значение делителя
    ssd1306_write_cmd(0xA8); // Set Multiplex Ratio
    ssd1306_write_cmd(0x3F); // Для высоты 32 строки (0x1F = 31)
    ssd1306_write_cmd(0xD3); // Set Display Offset
    ssd1306_write_cmd(0x00); // Смещение 0
    ssd1306_write_cmd(0x40); // Set Display Start Line
    ssd1306_write_cmd(0x8D); // Charge Pump
    ssd1306_write_cmd(0x14); // Включить Charge Pump
    ssd1306_write_cmd(0x20); // Memory Mode
    ssd1306_write_cmd(0x00); // Horizontal Addressing
    ssd1306_write_cmd(0xA1); // Segment Remap (смещение столбцов)
    ssd1306_write_cmd(0xC8); // COM Output Scan Direction
    ssd1306_write_cmd(0xDA); // Set COM Pins
    ssd1306_write_cmd(0x12); // Последовательная конфигурация COM
    ssd1306_write_cmd(0x81); // Set Contrast
    ssd1306_write_cmd(0xCF); // Значение контраста
    ssd1306_write_cmd(0xD9); // Set Precharge Period
    ssd1306_write_cmd(0xF1); // Фазы предзаряда
    ssd1306_write_cmd(0xDB); // Set VCOMH Deselect
    ssd1306_write_cmd(0x40); // Уровень VCOMH
    ssd1306_write_cmd(0xA4); // Display Resume
    ssd1306_write_cmd(0xA6); // Normal Display
    ssd1306_write_cmd(0xAF); // Display ON
}

void ssd1306_clear(void)
{
    for (int i = 0; i < sizeof(framebuffer); i++)
    {
        framebuffer[i] = 0x00;
    }
}

void ssd1306_update(void)
{
    for (uint8_t page = 0; page < SSD1306_PAGES; page++)
    {
        ssd1306_write_cmd(0xB0 | page); // Set Page Start Address for Page Addressing Mode
        ssd1306_write_cmd(0x00);        // Set Lower Column Start Address (usually 0)
        ssd1306_write_cmd(0x00);        // Set Higher Column Start Address (usually 0)
        ssd1306_write_data(&framebuffer[page * SSD1306_WIDTH], SSD1306_WIDTH);
    }
}

void ssd1306_draw_pixel(int x, int y, int color)
{
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT)
        return;

    uint16_t index = x + (y / 8) * SSD1306_WIDTH;
    uint8_t bit_mask = 1 << (y % 8);

    if (color)
    {
        framebuffer[index] |= bit_mask;
    }
    else
    {
        framebuffer[index] &= ~bit_mask;
    }
}

void ssd1306_draw_big_pixel(int x, int y, int color, int size)
{
    for (int k = 0; k < size; k++)
    {
        for (int l = 0; l < size; l++)
        {
            ssd1306_draw_pixel(size * x + k, size * y + l, color);
        }
    }
}

void ssd1306_draw_char(int x, int y, char ch)
{
    if (x > SSD1306_WIDTH - 6 || y > SSD1306_HEIGHT - 8)
        return;
    if (ch < 32 || ch > 126)
        ch = '?';

    const uint8_t *glyph = &font5x7[(ch - 32) * 5];

    for (int i = 0; i < 5; i++)
    {
        uint8_t column_data = glyph[i];
        for (int j = 0; j < 7; j++)
        {
            if (column_data & (1 << j))
            {
                ssd1306_draw_pixel(x + i, y + j, 1);
            }
            else
            {
                ssd1306_draw_pixel(x + i, y + j, 0);
            }
        }
    }
}

void ssd1306_fill(void)
{
    memset(framebuffer, 0xFF, sizeof(framebuffer)); // Все пиксели включены
}

void ssd1306_draw_string(int x, int y, char *str)
{
    while (*str)
    {
        if (x > SSD1306_WIDTH - 6)
        {
            break;
        }
        ssd1306_draw_char(x, y, *str++);
        x += 6;
    }
}

void *memset(void *ptr, int value, size_t num)
{
    unsigned char *p = ptr;
    while (num--)
    {
        *p++ = (unsigned char)value;
    }
    return ptr;
}