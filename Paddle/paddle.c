#include "paddle.h"
#include "../Board/board.h"
//#include "../GLCD/GLCD.h"
#include "../GLCD_Extended/GLCD_Extended.h"

uint16_t paddle_x = 100;
uint16_t paddle_x_next = 100;
const uint16_t paddle_max_speed = 5;
const uint16_t paddle_length = 40;
const uint16_t paddle_thickness = 10;
const uint16_t paddle_y_distance_from_bottom = 32 + paddle_thickness;
const uint16_t paddle_y = 320 - paddle_y_distance_from_bottom;
const uint16_t paddle_color = Green;

void draw_paddle(uint16_t x0, uint16_t length) {
	draw_thic_line_orizontal(x0, x0 + length, 278, 10, Green);
}

void move_paddle_right(uint16_t distance) {
	int x, y;
	for (x = paddle_x; x < paddle_x + distance; x++) {
		for (y = paddle_y; y < paddle_y + paddle_thickness; y++) {
			LCD_SetPoint(x, y, board_background_color);
			LCD_SetPoint(x + paddle_length, y, paddle_color);
		}
	}
	paddle_x = paddle_x + distance;
}

void move_paddle_left(uint16_t distance) {
	int x, y;
	for (x = paddle_x; x >= paddle_x - distance; x--) {
		for (y = paddle_y; y < paddle_y + paddle_thickness; y++) {
			LCD_SetPoint(x, y, paddle_color);
			LCD_SetPoint(x + paddle_length, y, board_background_color);
		}
	}
	paddle_x = paddle_x - distance;
}

void move_paddle_right_one_step() {
	int x, y;
	x = paddle_x + 1;
	for (y = paddle_y; y < paddle_y + paddle_thickness; y++) {
		LCD_SetPoint(x, y, board_background_color);
		LCD_SetPoint(x + paddle_length, y, paddle_color);
	}
	paddle_x = paddle_x + 1;
}

void move_paddle_left_one_step() {
	int x, y;
	x = paddle_x - 1;
	for (y = paddle_y; y < paddle_y + paddle_thickness; y++) {
		LCD_SetPoint(x, y, paddle_color);
		LCD_SetPoint(x + paddle_length, y, board_background_color);
	}
	paddle_x = paddle_x - 1;
}

void move_paddle_absolute_position(uint16_t new_paddle_x) {
	paddle_x_next = new_paddle_x;
	// MOVE RIGHT
	//if (paddle_x < new_paddle_x) {
	//	move_paddle_right(new_paddle_x - paddle_x);
	//}
	// MOVE LEFT
	//else if (paddle_x >=  new_paddle_x) {
	//	move_paddle_left(paddle_x - new_paddle_x);
	//}
}

int min(int a, int b) {
	if (a < b)
		return a;
	else return b;
}

void move_paddle_one_step_to_next_x() {
	// MOVE RIGHT
	if (paddle_x < paddle_x_next) {
		move_paddle_right(min(paddle_max_speed, paddle_x_next - paddle_x));
	}
	// MOVE LEFT
	else if (paddle_x >  paddle_x_next) {
		move_paddle_left(min(paddle_max_speed, paddle_x - paddle_x_next));
	}
}
