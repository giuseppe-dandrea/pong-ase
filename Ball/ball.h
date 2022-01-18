#ifndef _BALL_H_
#define _BALL_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"
#define BALL_SIZE 5
#define BALL_COLOR Green
#define BALL_X_INITIAL 235 - BALL_SIZE
#define BALL_Y_INITIAL 175
#define BALL_X_SPEED_INITIAL -3
#define BALL_Y_SPEED_INITIAL 3


void ball_initialize(void);
void ball_draw(void);
void ball_delete(void);
void ball_move(void);
void ball_reset(void);

#endif
