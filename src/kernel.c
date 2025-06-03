// #include "interrupt.h"
#include "keyboard.h"
#include "ssd1306.h"
#include "gpio.h"
#include "game.h"

char str[] = {'S', 'c', 'o', 'r', 'e', ':', '0', '0', '0'}; 

void update_score_string() {
    int i = 0;
    int N = get_current_score();

    // Reverse the string to get the correct order
    for (int j = 0, k = 8; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }

    str[0] = '0';
    str[1] = '0';
    str[2] = '0';

    // Extract digits from the number and add them to the
    // string
    while (N > 0) {
      
        // Convert integer digit to character and store
        // it in the str
        str[i++] = N % 10 + '0';
        N /= 10;
    } 

    // Reverse the string to get the correct order
    for (int j = 0, k = 8; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
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
            ssd1306_draw_string(0, 0, str);

            for (int j = 0; j < MAX_Y; j++)
            {
                for (int i = 0; i < MAX_X; i++)
                {
                    ssd1306_draw_big_pixel(i, j + 4, matrix[j][i], 4);
                }
            }

            ssd1306_update();
            //delay(10000);
        }

        while (get_is_game_over())
        {
            ssd1306_clear();
            ssd1306_draw_string(30, 28, "Game Over!");
            ssd1306_draw_string(0, 0, str);
            ssd1306_update();

            char pressed_key = scan_keyboard();
            if (pressed_key == '5')
            {
                break; 
            }

            //delay(10000);
        }
    }
}

