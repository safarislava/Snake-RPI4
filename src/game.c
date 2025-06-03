#include <stdint.h>
#include "game.h"
#include "gpio.h"

uint8_t matrix[MAX_Y][MAX_X] = {0};

int is_game_over;
int head_x, head_y; // position of snake head
direction *p_current_direction = &(direction){0, 0};
int tail_x[MAX_X * MAX_Y], tail_y[MAX_X * MAX_Y], tail_size; // array for tail in x and y, size of tail
int food_x, food_y;                                      // food position
int is_wall_collision_enabled;
int current_score;
uint32_t seed = 1;

uint32_t rand(void) {
    seed = (1103515245 * seed + 12345) & 0x7FFFFFFF;
    return seed;
}

int get_is_game_over()
{
    return is_game_over;
}

int get_current_score()
{
    return current_score;
}

void init_game()
{
    is_game_over = 0;
    head_x = MAX_X / 2;
    head_y = MAX_Y / 2; 
    *p_current_direction = (direction){0, 0};

    for (int i = 0; i < MAX_X * MAX_Y; i++)
    {
        tail_x[i] = 0;
        tail_y[i] = 0;
    }
    
    tail_size = 0; 
    food_x = 1;
    food_y = 1;                                      
    is_wall_collision_enabled = 0;
    current_score = 0;

    seed = 1;
    food_x = rand() % (MAX_X - 1);
    food_y = rand() % (MAX_Y - 1);

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            matrix[j][i] = 0; // Clear the matrix
        }
    }


}

void update_matrix()
{
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            if (i == head_x && j == head_y)
            {
                matrix[j][i] = 1;
            }
            else if (i == food_x && j == food_y)
            {
                matrix[j][i] = 1;
            }
            else
            {
                uint8_t rend_space = 0;
                for (int k = 0; k < tail_size; k++)
                {
                    if (tail_x[k] == i && tail_y[k] == j)
                    {
                        matrix[j][i] = 1;
                        rend_space = 1;
                    }
                }
                if (!rend_space)
                {
                    matrix[j][i] = 0;
                }
            }
        }
    }
}

void input(char key)
{
    switch (key)
    {
    case '2':
        if (!compare_directions(*p_current_direction, DOWN))
        {
            *p_current_direction = UP;
        }
        break;
    case '8':
        if (!compare_directions(*p_current_direction, UP))
        {
            *p_current_direction = DOWN;
        }
        break;
    case '4':
        if (!compare_directions(*p_current_direction, RIGHT))
        {
            *p_current_direction = LEFT;
        }
        break;
    case '6':
        if (!compare_directions(*p_current_direction, LEFT))
        {
            *p_current_direction = RIGHT;
        }
        break;
    }
}

void game()
{

if (head_x == food_x && head_y == food_y)
    {
        led_on();
        //delay(10000);
        led_off();
        current_score += 1;
        tail_size++;

        int is_food_in_valid_position = 0;
        while (!is_food_in_valid_position)
        {
            food_x = rand() % (MAX_X - 1);
            food_y = rand() % (MAX_Y - 1);
            is_food_in_valid_position = 1;

            if (food_x == head_x && food_y == head_y)
            {
                is_food_in_valid_position = 0;
                continue;
            }

            for (int i = 0; i < tail_size; i++)
            {
                if (food_x == tail_x[i] && food_y == tail_y[i])
                {
                    is_food_in_valid_position = 0;
                    break;
                }
            }
        }
    }
    
    // Move tail
    for (int i = tail_size - 1; i > 0; i--)
    {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }

    if (tail_size > 0)
    {
        tail_x[0] = head_x;
        tail_y[0] = head_y;
    }

    head_x += p_current_direction->delta_x;
    head_y += p_current_direction->delta_y;

    // Check wall collision
    if (is_wall_collision_enabled)
    {
        if ((head_x < 0) || (head_x > MAX_X - 1) || (head_y < 0) || (head_y > MAX_Y - 1))
        {
            is_game_over = 1;
        }
    }
    else
    {
        if (head_x < 0)
        {
            head_x = MAX_X - 1;
        }
        if (head_x > MAX_X - 1)
        {
            head_x = 0;
        }
        if (head_y < 0)
        {
            head_y = MAX_Y - 1;
        }
        if (head_y > MAX_Y - 1)
        {
            head_y = 0;
        }
    }

    // Check self collision
    for (int i = 0; i < tail_size; i++)
    {
        if (tail_x[i] == head_x && tail_y[i] == head_y)
        {
            is_game_over = 1;
        }
    }

    // Check food collection
    
}

int compare_directions(direction direction1, direction direction2)
{
    return direction1.delta_x == direction2.delta_x && direction1.delta_y == direction2.delta_y;
}