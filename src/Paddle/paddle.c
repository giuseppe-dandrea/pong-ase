#include "paddle.h"
#include "../Board/board.h"
//#include "../GLCD/GLCD.h"
#include "../GLCD_Extended/GLCD_Extended.h"

uint16_t paddle_x = 100;
uint16_t paddle_x_next = 100;


void paddle_draw(uint16_t x0, uint16_t length) {
	draw_thic_line_orizontal(x0, x0 + length, PADDLE_Y, PADDLE_THICKNESS, Green);
}

void paddle_move_right(uint16_t distance) {
	int x, y;
	for (x = paddle_x; x < paddle_x + distance; x++) {
		for (y = PADDLE_Y; y < PADDLE_Y + PADDLE_THICKNESS; y++) {
			LCD_SetPoint(x, y, BOARD_BACKGROUND_COLOR);
			LCD_SetPoint(x + PADDLE_LENGTH, y, PADDLE_COLOR);
		}
	}
	paddle_x = paddle_x + distance;
}

void move_paddle_left(uint16_t distance) {
	int x, y;
	for (x = paddle_x; x >= paddle_x - distance; x--) {
		for (y = PADDLE_Y; y < PADDLE_Y + PADDLE_THICKNESS; y++) {
			LCD_SetPoint(x, y, PADDLE_COLOR);
			LCD_SetPoint(x + PADDLE_LENGTH, y, BOARD_BACKGROUND_COLOR);
		}
	}
	paddle_x = paddle_x - distance;
}

void paddle_update_position(uint16_t new_paddle_x) {
	paddle_x_next = new_paddle_x;
}

int min(int a, int b) {
	if (a < b)
		return a;
	else return b;
}

void paddle_move_one_step() {
	// MOVE RIGHT
	if (paddle_x < paddle_x_next) {
		paddle_move_right(min(PADDLE_MAX_SPEED, paddle_x_next - paddle_x));
	}
	// MOVE LEFT
	else if (paddle_x > paddle_x_next) {
		move_paddle_left(min(PADDLE_MAX_SPEED, paddle_x - paddle_x_next));
	}
}
