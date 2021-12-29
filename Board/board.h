#ifndef _BOARD_H_
#define _BOARD_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

static const uint16_t board_min_x = 5;
static const uint16_t board_max_x = 235;
static const uint16_t board_min_y = 5;
static const uint16_t board_max_y = 320;
static const uint16_t border_thickness = 5;
static const uint16_t board_background_color = Black;

void draw_initial_game_board(void);
void increase_score(void);

#endif
