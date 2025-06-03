#pragma once

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#define MAX_X 32
#define MAX_Y 12
#define HEAD_SYMBOL "O"
#define TAIL_SYMBOL "o"
#define FOOD_SYMBOL "F"
#define WALL_SYMBOL "#"

struct MoveDirection {
    int delta_x;
    int delta_y;
};

#define direction struct MoveDirection

extern uint8_t matrix[MAX_Y][MAX_X];

void init_game();
void update_matrix();
void input(char key);
void game();
int get_is_game_over();
int get_current_score();

/*
@return 1 if equal, else 0
*/
int compare_directions(direction direction1, direction direction2); 

#define UP (direction) {.delta_x=0, .delta_y=-1}
#define DOWN (direction) {.delta_x=0, .delta_y=1}
#define LEFT (direction) {.delta_x=-1, .delta_y=0}
#define RIGHT (direction) {.delta_x=1, .delta_y=0}

#endif