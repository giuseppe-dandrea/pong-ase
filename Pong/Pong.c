#include "Pong.h"
#include "../Board/board.h"
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"
#include "../timer/timer.h"
#include <stdlib.h>
#include <time.h>

int GAME_ON;
int GAME_LOST;
int GAME_PAUSED;
int GAME_RESET;
uint16_t sound_duration = 0;
extern uint16_t ball_x, ball_y, score;


void pong_main_menu() {	
	LCD_Clear(Black);
	GUI_Text(100, 80, (uint8_t *) "PONG", White, Black);
	GUI_Text(40, 120, (uint8_t *) "Press KEY1 to start", White, Black);
}

void pong_initialize_game() {
	initialize_ball();
	draw_initial_game_board();
	GAME_ON = 0;
}

void pong_start_game() {
	clear_central_text();
	GAME_ON = 1;
	GAME_RESET = 0;
	GAME_PAUSED = 0;
}

void pong_game_lost() {
	char str[] = "You Lose";
	pong_play_sound_game_lost();
	GAME_ON = 0;
	GAME_PAUSED = 0;
	GAME_LOST = 1;
	GUI_Text(GAME_LOST_STRING_X, GAME_LOST_STRING_Y, (uint8_t *) str, White, Black);
}

void pong_pause_game(void) {
	char str[] = "Pause";
	GAME_ON = 0;
	GAME_PAUSED = 1;
	GUI_Text(GAME_PAUSED_STRING_X, GAME_PAUSED_STRING_Y, (uint8_t *) str, White, Black);
}

void clear_pause_string() {
	int x, y;
	for (x = GAME_PAUSED_STRING_X; x < GAME_PAUSED_STRING_X + GAME_CHAR_WIDTH * 5; x++)
		for (y = GAME_PAUSED_STRING_Y; y < GAME_PAUSED_STRING_Y + GAME_CHAR_HEIGHT; y++)
			LCD_SetPoint(x, y, Black);
}

void pong_resume_game(void) {
	GAME_ON = 1;
	GAME_PAUSED = 0;
	clear_pause_string();
	draw_ball(ball_x, ball_y);
}

void pong_reset_game(void) {
	GAME_ON = 0;
	GAME_PAUSED = 0;
	GAME_RESET = 1;
	score = 0;
	delete_ball();
	reset_ball();
	draw_reset_game_board();
}

void pong_play_sound(uint16_t freq, uint16_t duration) {
	int k = 25000000 / (freq * 45);
	sound_duration = duration;
	disable_timer(0);
	reset_timer(0);
	init_timer(0, k);
	enable_timer(0);
}

void pong_play_sound_game_lost(void) {
	pong_play_sound(90, 2500);
}

void pong_play_sound_wall(void) {
	pong_play_sound(131, 10);
}
void pong_play_sound_paddle(void) {
	pong_play_sound(196, 50);
}
