#ifndef _PONG_H_
#define _PONG_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

#define GAME_LOST_STRING_X 85
#define GAME_LOST_STRING_Y 140
#define GAME_PAUSED_STRING_X 95
#define GAME_PAUSED_STRING_Y 140
#define GAME_CHAR_WIDTH  9
#define GAME_CHAR_HEIGHT  17


void pong_main_menu(void);
void pong_initialize_game(void);
void pong_main_game_cycle(void);
void pong_draw_best_score(void);
void pong_draw_score(void);
void pong_game_lost(void);
void pong_pause_game(void);
void pong_resume_game(void);

#endif
