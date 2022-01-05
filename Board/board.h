#ifndef _BOARD_H_
#define _BOARD_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

#define BOARD_MIN_X 5
#define BOARD_MAX_X  235
#define BOARD_MIN_Y  5
#define BOARD_MAX_Y  320
#define BORDER_THICKNESS  5
#define BOARD_BACKGROUND_COLOR  Black

#define SCORE_X  BOARD_MIN_X
#define SCORE_Y  (BOARD_MAX_Y - 16) / 2
#define BEST_SCORE_X  BOARD_MAX_X - 4 * 8
#define BEST_SCORE_Y  BOARD_MIN_Y
#define SCORE_NUMBER_WIDTH  9
#define SCORE_NUMBER_HEIGHT  17
#define SCORE_MAX_X  SCORE_X + SCORE_NUMBER_WIDTH * 4 + 5
#define SCORE_MAX_Y  SCORE_Y + SCORE_NUMBER_HEIGHT + 5
#define BEST_SCORE_MAX_X  BEST_SCORE_X + SCORE_NUMBER_WIDTH * 4 + 5
#define BEST_SCORE_MAX_Y  BEST_SCORE_Y + SCORE_NUMBER_HEIGHT + 5

void draw_initial_game_board(void);
void draw_reset_game_board(void);
void increase_score(void);
void clear_central_text(void);

#endif
