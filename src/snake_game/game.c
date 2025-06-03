#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "game.h"

int is_game_over = 0;
int head_x = MAX_X / 2, head_y = MAX_Y / 2; // position of snake head
direction *p_current_direction = &(direction){0, 0};
int tail_x[MAX_X * MAX_Y], tail_y[MAX_X * MAX_Y], tail_size = 0; // array for tail in x and y, size of tail
int food_x = 1, food_y = 1;                                      // food position
int is_wall_collision_enabled = 1;
int current_score = 0;
int record_score = 0;
FILE *data;

void init()
{
    data = fopen("data", "rb");
    if (data)
    {
        // record = 10;
        // fwrite(&record,sizeof(int),1,data);
        fread(&record_score, sizeof(int), 1, data);
        fclose(data);
    }

    srand(time(NULL));
    food_x = rand() % (MAX_X - 1);
    food_y = rand() % (MAX_Y - 1);
}

void draw()
{
    int i, j, k;
    for (i = 0; i < MAX_X + 2; i++)
    {
        printf(WALL_SYMBOL);
    }

    printf("\n");
    for (i = 0; i < MAX_X; i++)
    {
        for (j = 0; j < MAX_Y; j++)
        {
            if (j == 0)
            {
                printf(WALL_SYMBOL);
            }
            if (j == head_x && i == head_y)
            {
                printf(HEAD_SYMBOL);
            }
            else if (j == food_x && i == food_y)
            {
                printf(FOOD_SYMBOL);
            }
            else
            {
                int rend_space = 0;
                for (k = 0; k < tail_size; k++)
                {
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        printf(TAIL_SYMBOL);
                        rend_space = 1;
                    }
                }
                if (rend_space != 1)
                {
                    printf(" ");
                }
            }
            if (j == MAX_X - 1)
            {
                printf(WALL_SYMBOL);
            }
        }
        printf("\n");
    }

    for (i = 0; i < MAX_X + 2; i++)
    {
        printf(WALL_SYMBOL);
    }

    printf("\nScore: %d", current_score);
    printf("\nRecord: %d", record_score);
}

void input()
{
    while (_kbhit())
    {
        switch (getch())
        {
        case 'w':
            if (!compare_directions(*p_current_direction, DOWN))
            {
                *p_current_direction = UP;
            }
            break;
        case 's':
            if (!compare_directions(*p_current_direction, UP))
            {
                *p_current_direction = DOWN;
            }
            break;
        case 'a':
            if (!compare_directions(*p_current_direction, RIGHT))
            {
                *p_current_direction = LEFT;
            }
            break;
        case 'd':
            if (!compare_directions(*p_current_direction, LEFT))
            {
                *p_current_direction = RIGHT;
            }
            break;
        }
    }
}

void game()
{
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
    if (head_x == food_x && head_y == food_y)
    {

        current_score += 10;
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
}

int main()
{
    init();

    while (!is_game_over)
    {
        input();
        game();
        draw();
        Sleep(80);
        system("cls");
    }

    if (current_score > record_score)
    {
        data = fopen("data", "wb");
        if (data == NULL)
        {
            printf("Fail in save the new RECORD!\n");
            exit(1);
        }
        fwrite(&current_score, sizeof(int), 1, data);
        fclose(data);
        printf("********************\n");
        printf("***  NEW RECORD  ***\n");
        printf("********************\n");
        printf("NEW RECORD: %d\n\n", current_score);
        system("pause");
    }
    else
    {
        printf("!!!!!!!!!!!!!!!!!\n");
        printf("!!! GAME OVER !!!\n");
        printf("!!!!!!!!!!!!!!!!!\n");
        printf("SCORE: %d\n", current_score);
        if (current_score != record_score)
        {
            printf("RECORD: %d\n", record_score);
        }
        system("pause");
    }

    return 0;
}

int compare_directions(direction direction1, direction direction2)
{
    return direction1.delta_x == direction2.delta_x && direction1.delta_y == direction2.delta_y;
}