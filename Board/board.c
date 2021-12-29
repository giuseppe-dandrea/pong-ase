#include "board.h"
#include <stdio.h>
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"


int score = 0;
int best_score = 100;
const int score_x = board_min_x;
const int score_y = (board_max_y - 16) / 2;
const int best_score_x = board_max_x - 4 * 8;
const int best_score_y = board_min_y;
const int score_number_width = 9;
const int score_number_height = 17;
const int score_max_x = score_x + score_number_width * 4;
const int score_max_y = score_y + score_number_height;
const int best_score_max_x = best_score_x + score_number_width * 4;
const int best_score_max_y = best_score_y + score_number_height;

extern uint16_t paddle_x, paddle_length;
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
  GUI_Text(best_score_x, best_score_y, (uint8_t *) str, White, Black);
}

// draws the score value on the screen
void draw_score() {
  char str[5];
  snprintf(str, 5, "%04d", score);
  GUI_Text(score_x, score_y, (uint8_t *) str, White, Black);
}

void draw_initial_game_board() {
	LCD_Clear(Black);
	draw_borders();
	draw_ball(ball_x, ball_y);
	draw_paddle(paddle_x, paddle_length);
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
