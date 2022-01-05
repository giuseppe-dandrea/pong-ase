#include "board.h"
#include <stdio.h>
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"
#include "../Pong/Pong.h"


extern uint16_t paddle_x;
extern uint16_t ball_x, ball_y;
extern uint16_t score, best_score;

void board_draw_borders() {
	draw_thic_line_orizontal(0, 240, 0, 5, Red);
	draw_thic_line_vertical(0, 0, 278, 5, Red);
	draw_thic_line_vertical(235, 0, 278, 5, Red);
}

// draws the best score value on the screen
void board_draw_best_score() {
  char str[5];
  snprintf(str, 5, "%04d", best_score);
  GUI_Text(BEST_SCORE_X, BEST_SCORE_Y, (uint8_t *) str, White, Black);
}

// draws the score value on the screen
void board_draw_score() {
  char str[5];
  snprintf(str, 5, "%04d", score);
  GUI_Text(SCORE_X, SCORE_Y, (uint8_t *) str, White, Black);
}

void board_draw_welcome_message() {
	GUI_Text(100, 100, (uint8_t *) "PONG", White, Black);
	GUI_Text(40, 120, (uint8_t *) "Press KEY1 to start", White, Black);
}

void board_draw_initial_game_board() {
	LCD_Clear(Black);
	board_draw_borders();
	board_draw_welcome_message();
	ball_draw(ball_x, ball_y);
	paddle_draw(paddle_x, PADDLE_LENGTH);
	board_draw_score();
	board_draw_best_score();
}

void board_clear_central_text() {
	int x, y;
	for (y = 100; y < 138; y++)
		for (x = 40; x < 200; x++)
			LCD_SetPoint(x, y, Black);
}

void board_draw_reset_game_board() {
	board_clear_central_text();
	board_draw_welcome_message();
	ball_draw(ball_x, ball_y);
	board_draw_score();
	board_draw_best_score();
}
