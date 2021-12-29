#ifndef _PONG_H_
#define _PONG_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

void pong_main_menu(void);
void pong_initialize_game(void);
void pong_main_game_cycle(void);
void pong_draw_best_score(void);
void pong_draw_score(void);

#endif
