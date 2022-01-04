#include "board.h"
#include <stdio.h>
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"
#include "../Pong/Pong.h"


int score = 0;
int best_score = 100;


extern uint16_t paddle_x;
extern uint16_t ball_x, ball_y;

void draw_borders() {
	draw_thic_line_orizontal(0, 240, 0, 5, Red);
	draw_thic_line_vertical(0, 0, 278, 5, Red);
	draw_thic_line_vertical(235, 0, 278, 5, Red);
}

// draws the best score value on the screen
void draw_best_score() {
  char str[5];
  snprintf(str, 5, "%04d", best_score);
  GUI_Text(BEST_SCORE_X, BEST_SCORE_Y, (uint8_t *) str, White, Black);
}

// draws the score value on the screen
void draw_score() {
  char str[5];
  snprintf(str, 5, "%04d", score);
  GUI_Text(SCORE_X, SCORE_Y, (uint8_t *) str, White, Black);
}

void draw_initial_game_board() {
	LCD_Clear(Black);
	draw_borders();
	draw_ball(ball_x, ball_y);
	draw_paddle(paddle_x, PADDLE_LENGTH);
	draw_score();
	draw_best_score();
}

void clear_central_text() {
	int x, y;
	for (x = 50; x < 190; x++)
		for (y = GAME_LOST_STRING_Y; y < GAME_LOST_STRING_Y + 30; y++)
			LCD_SetPoint(x, y, Black);
}

void draw_reset_game_board() {
	clear_central_text();
	draw_ball(ball_x, ball_y);
	draw_score();
	draw_best_score();
}

void increase_score() {
	if (score > 100)
		score += 5;
	score += 5;
	draw_score();
	if (score > best_score) {
		best_score = score;
		draw_best_score();
	}
}
