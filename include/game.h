#pragma once

#include "common.h"

#define MAX_X 32
#define MAX_Y 12

#define direction struct MoveDirection

#define UP (direction){.delta_x = 0, .delta_y = -1}
#define DOWN (direction){.delta_x = 0, .delta_y = 1}
#define LEFT (direction){.delta_x = -1, .delta_y = 0}
#define RIGHT (direction){.delta_x = 1, .delta_y = 0}

struct MoveDirection
{
    int delta_x;
    int delta_y;
};

// extern u8 matrix[MAX_Y][MAX_X];
// Уберите extern u8 matrix[MAX_Y][MAX_X];
// И добавьте функции для доступа:
int* get_matrix_ptr();
void set_matrix_value(int x, int y, int value);
int get_matrix_value(int x, int y);

void init_game();
void update_matrix();
void input(char key);
void game();
u8 get_is_game_over();
u8 get_current_score();
u8 compare_directions(direction direction1, direction direction2);

