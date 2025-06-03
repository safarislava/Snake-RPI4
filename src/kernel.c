#include "keyboard.h"
#include "ssd1306.h"
#include "gpio.h"
#include "game.h"

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

void kernel_main(void)
{
    gpio_init();
    keyboard_init();
    ssd1306_init();
    // setup_gpio_interrupts();
    // enable_irq();

    ssd1306_clear();
    ssd1306_update();

    while (1)
    {
        init_game();

        while (!get_is_game_over())
        {
            ssd1306_clear();
            char pressed_key = scan_keyboard();
            input(pressed_key);
            game();

            update_matrix();

            update_score_string();
            ssd1306_draw_string(0, 0, score_string);

            for (int j = 0; j < MAX_Y; j++)
            {
                for (int i = 0; i < MAX_X; i++)
                {
                    ssd1306_draw_big_pixel(i, j + 4, matrix[j][i], 4);
                }
            }

            ssd1306_update();
            // delay(10000);
        }

        while (get_is_game_over())
        {
            ssd1306_clear();
            ssd1306_draw_string(30, 28, "Game Over!");
            ssd1306_draw_string(0, 0, score_string);
            ssd1306_update();

            char pressed_key = scan_keyboard();
            if (pressed_key == '5')
            {
                break;
            }
            // delay(10000);
        }
    }
}
