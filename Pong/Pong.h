#ifndef _PONG_H_
#define _PONG_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

#define GAME_LOST_STRING_X 85
#define GAME_LOST_STRING_Y 120
#define GAME_PAUSED_STRING_X 95
#define GAME_PAUSED_STRING_Y 120
#define GAME_CHAR_WIDTH  9
#define GAME_CHAR_HEIGHT  17


void pong_initialize_game(void);
void pong_start_game(void);
void pong_game_lost(void);
void pong_pause_game(void);
void pong_resume_game(void);
void pong_reset_game(void);
void pong_play_sound_game_lost(void);
void pong_play_sound_wall(void);
void pong_play_sound_paddle(void);
void pong_increase_score(void);

#endif
