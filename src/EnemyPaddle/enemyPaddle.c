#include "enemyPaddle.h"
#include "../Board/board.h"
#include "../Ball/ball.h"
//#include "../GLCD/GLCD.h"
#include "../GLCD_Extended/GLCD_Extended.h"

uint16_t enemy_paddle_x = 100;
uint16_t enemy_paddle_x_next = 100;

extern uint16_t ball_x, ball_x_speed;


void enemy_paddle_draw(uint16_t x0, uint16_t length) {
	draw_thic_line_orizontal(x0, x0 + length, ENEMY_PADDLE_Y, ENEMY_PADDLE_THICKNESS, Green);
}

void enemy_paddle_move_right(uint16_t distance) {
	int x, y;
	for (x = enemy_paddle_x; x < enemy_paddle_x + distance; x++) {
		for (y = ENEMY_PADDLE_Y; y < ENEMY_PADDLE_Y + ENEMY_PADDLE_THICKNESS; y++) {
			LCD_SetPoint(x, y, BOARD_BACKGROUND_COLOR);
			LCD_SetPoint(x + ENEMY_PADDLE_LENGTH, y, ENEMY_PADDLE_COLOR);
		}
	}
	enemy_paddle_x = enemy_paddle_x + distance;
}

void move_enemy_paddle_left(uint16_t distance) {
	int x, y;
	for (x = enemy_paddle_x; x >= enemy_paddle_x - distance; x--) {
		for (y = ENEMY_PADDLE_Y; y < ENEMY_PADDLE_Y + ENEMY_PADDLE_THICKNESS; y++) {
			LCD_SetPoint(x, y, ENEMY_PADDLE_COLOR);
			LCD_SetPoint(x + ENEMY_PADDLE_LENGTH, y, BOARD_BACKGROUND_COLOR);
		}
	}
	enemy_paddle_x = enemy_paddle_x - distance;
}

void enemy_paddle_update_position(uint16_t new_enemy_paddle_x) {
	enemy_paddle_x_next = new_enemy_paddle_x;
}

void enemy_paddle_find_next_position() {
	int16_t next_position = ball_x + ball_x_speed - (ENEMY_PADDLE_LENGTH / 2);
	if (next_position < BOARD_MIN_X)
		next_position = BOARD_MIN_X;
	else if (next_position + ENEMY_PADDLE_LENGTH > BOARD_MAX_X)
		next_position = BOARD_MAX_X - ENEMY_PADDLE_LENGTH;
	enemy_paddle_x_next = (uint16_t)next_position;
}

int _min(int a, int b) {
	if (a < b)
		return a;
	else return b;
}

void enemy_paddle_move_one_step() {
	// MOVE RIGHT
	if (enemy_paddle_x < enemy_paddle_x_next) {
		enemy_paddle_move_right(_min(ENEMY_PADDLE_MAX_SPEED, enemy_paddle_x_next - enemy_paddle_x));
	}
	// MOVE LEFT
	else if (enemy_paddle_x > enemy_paddle_x_next) {
		move_enemy_paddle_left(_min(ENEMY_PADDLE_MAX_SPEED, enemy_paddle_x - enemy_paddle_x_next));
	}
}
