#pragma once

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#define MAX_X 32
#define MAX_Y 12

#define direction struct MoveDirection

#define UP (direction){.delta_x = 0, .delta_y = -1}
#define DOWN (direction){.delta_x = 0, .delta_y = 1}
#define LEFT (direction){.delta_x = -1, .delta_y = 0}
#define RIGHT (direction){.delta_x = 1, .delta_y = 0}

struct MoveDirection
{
    uint8_t delta_x;
    uint8_t delta_y;
};

extern uint8_t matrix[MAX_Y][MAX_X];

void init_game();
void update_matrix();
void input(char key);
void game();
uint8_t get_is_game_over();
uint8_t get_current_score();
uint8_t compare_directions(direction direction1, direction direction2);

#endif