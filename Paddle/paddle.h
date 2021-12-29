#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

void draw_paddle(uint16_t x0, uint16_t length);
void move_paddle_right(uint16_t distance);
void move_paddle_absolute_position(uint16_t new_paddle_x);
void move_paddle_one_step_to_next_x(void);

#endif
