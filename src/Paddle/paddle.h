#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

#define PADDLE_MAX_SPEED  10
#define PADDLE_LENGTH  40
#define PADDLE_THICKNESS  10
#define PADDLE_Y_FROM_BOTTOM  (32 + PADDLE_THICKNESS)
#define PADDLE_Y  (320 - PADDLE_Y_FROM_BOTTOM)
#define PADDLE_COLOR  Green

void paddle_draw(uint16_t x0, uint16_t length);
void paddle_update_position(uint16_t new_paddle_x);
void paddle_move_one_step(void);

#endif
