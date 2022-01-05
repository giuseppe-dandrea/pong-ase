#ifndef _BALL_H_
#define _BALL_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"
#define BALL_SIZE 5
#define BALL_COLOR Green
#define BALL_X_INITIAL 235 - BALL_SIZE
#define BALL_Y_INITIAL 150
#define BALL_X_SPEED_INITIAL -5
#define BALL_Y_SPEED_INITIAL 5


void ball_initialize(void);
void ball_draw(uint16_t x0, uint16_t y0);
void ball_delete(void);
void ball_move(void);
void ball_reset(void);

#endif
