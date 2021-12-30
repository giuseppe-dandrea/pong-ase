#ifndef _BALL_H_
#define _BALL_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"
#define BALL_SIZE 5
#define BALL_COLOR Green


void draw_ball(uint16_t x0, uint16_t y0);
void move_ball(void);
void initialize_ball(void);

#endif
