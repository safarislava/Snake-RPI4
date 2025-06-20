#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "led.h"
#include "keyboard.h"
#include "ssd1306.h"
#include "game.h"

void putc(void *p, char c)
{
    if (c == '\n')
    {
        uart_send('\r');
    }

    uart_send(c);
}

u32 get_el();

char score_string[] = {'S', 'c', 'o', 'r', 'e', ':', '0', '0', '0'};

void update_score_string()
{
    uint8_t i = 0;
    uint8_t N = get_current_score();

    for (int j = 0, k = 8; j < k; j++, k--)
    {
        char temp = score_string[j];
        score_string[j] = score_string[k];
        score_string[k] = temp;
    }

    score_string[0] = '0';
    score_string[1] = '0';
    score_string[2] = '0';

    while (N > 0)
    {
        score_string[i++] = N % 10 + '0';
        N /= 10;
    }

    for (int j = 0, k = 8; j < k; j++, k--)
    {
        char temp = score_string[j];
        score_string[j] = score_string[k];
        score_string[k] = temp;
    }
}

void kernel_main()
{
    uart_init();
    init_printf(0, putc);
    printf("\nRasperry PI Bare Metal OS Initializing...\n");

    irq_init_vectors();
    enable_interrupt_controller();
    irq_enable();

    ssd1306_init();
    ssd1306_clear();
    ssd1306_update();

    led_init();
    keyboard_init();
    timer_init();

    printf("Initialization Complete!\n");

    // printf("\tBoard: Raspberry PI 4\n");

    // printf("\nException Level: %d\n", get_el());

    int i = 0;

    while (1)
    {
        // timer_sleep(500);
        init_game();

        for (int j = 0; j < MAX_Y; j++)
        {
            for (int i = 0; i < MAX_X; i++)
            {
                // ssd1306_draw_pixel(i, j, matrix[j][i]);
                printf("%d ", get_matrix_value(i, j));
                ssd1306_draw_big_pixel(i, j + 4, get_matrix_value(i, j), 4);
            }

            printf("\n");
        }

        while (!get_is_game_over())
        {
            printf("Loop %d\n", i++);

            ssd1306_clear();

            irq_disable();
            game();

            update_matrix();

            update_score_string();
            ssd1306_draw_string(0, 0, score_string);

            for (int j = 0; j < MAX_Y; j++)
            {
                for (int i = 0; i < MAX_X; i++)
                {
                    // ssd1306_draw_pixel(i, j, matrix[j][i]);
                    printf("%d ", get_matrix_value(i, j));
                    ssd1306_draw_big_pixel(i, j + 4, get_matrix_value(i, j), 4);
                }

                printf("\n");
            }

            ssd1306_update();
            irq_enable();
            // delay(10000);
        }

        while (get_is_game_over())
        {
            ssd1306_clear();
            ssd1306_draw_string(30, 28, "Game Over!");
            ssd1306_draw_string(0, 0, score_string);
            ssd1306_update();

            // char pressed_key = scan_keyboard();
            // if (pressed_key == '5')
            // {
            //     break;
            // }
            // delay(10000);
        }

        // char symbol = scan_keyboard();
        // if (symbol != 'Z') {
        // printf("Symbol: %c\n", symbol);
        // }
    }
}
