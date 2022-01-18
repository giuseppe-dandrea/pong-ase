#ifndef _ENEMY_PADDLE_H_
#define _ENEMY_PADDLE_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

#define ENEMY_PADDLE_MAX_SPEED  10
#define ENEMY_PADDLE_LENGTH  40
#define ENEMY_PADDLE_THICKNESS  10
#define ENEMY_PADDLE_Y  32
#define ENEMY_PADDLE_COLOR  Green

void enemy_paddle_draw(uint16_t x0, uint16_t length);
void enemy_paddle_update_position(uint16_t new_enemy_paddle_x);
void enemy_paddle_move_one_step(void);
void enemy_paddle_find_next_position(void);

#endif
