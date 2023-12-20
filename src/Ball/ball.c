#include "ball.h"
#include "../Pong/Pong.h"
#include "../Board/board.h"
#include "../Paddle/paddle.h"
#include "../EnemyPaddle/enemyPaddle.h"
#include "../GLCD/GLCD.h"
#include <stdlib.h>

uint16_t ball_x = 5;
uint16_t ball_y = 10;
int16_t ball_x_speed = 5;
int16_t ball_y_speed = 5;

uint16_t **ball_background_buffer_matrix;
uint8_t BUFFER_FULL_FLAG = 0;

extern uint16_t paddle_x, enemy_paddle_x;

extern int score, enemy_score;
extern int GAME_PAUSED;

void ball_reset() {
	ball_x = BALL_X_INITIAL;
	ball_y = BALL_Y_INITIAL;
	ball_x_speed = BALL_X_SPEED_INITIAL;
	ball_y_speed = BALL_Y_SPEED_INITIAL;
}

void ball_initialize() {
	int i;
	ball_reset();
	ball_background_buffer_matrix = (uint16_t**) malloc(BALL_SIZE * sizeof(uint16_t *));
	for (i = 0; i < BALL_SIZE; i++)
		ball_background_buffer_matrix[i] = (uint16_t*) malloc(BALL_SIZE * sizeof(uint16_t));
}

void ball_handle_paddle_collision() {
	int ball_switch_position;
	int ball_relative_position = ball_x - paddle_x;
	if (ball_relative_position < 0)
		ball_relative_position += BALL_SIZE;
	else if (ball_relative_position > PADDLE_LENGTH)
		ball_relative_position -= BALL_SIZE;
	else
		ball_relative_position += BALL_SIZE / 2;
	
	ball_switch_position = ball_relative_position * 5 / PADDLE_LENGTH;
	
	switch (ball_switch_position) {
		case 0:
			ball_x_speed = -7;
			ball_y_speed = -3;
			break;
		case 1:
			ball_x_speed = -5;
			ball_y_speed = -5;
			break;
		case 2:
			ball_x_speed = (rand() % 3) - 1;
			ball_y_speed = -7;
			break;
		case 3:
			ball_x_speed = 5;
			ball_y_speed = -5;
			break;
		case 4:
			ball_x_speed = 7;
			ball_y_speed = -3;
			break;
	}
	
	ball_x_speed += (rand() % 3) - 1;
	ball_y_speed += (rand() % 2) - 1;
}

void ball_handle_enemy_paddle_collision() {
	int ball_switch_position;
	int ball_relative_position = ball_x - enemy_paddle_x;
	if (ball_relative_position < 0)
		ball_relative_position += BALL_SIZE;
	else if (ball_relative_position > ENEMY_PADDLE_LENGTH)
		ball_relative_position -= BALL_SIZE;
	else
		ball_relative_position += BALL_SIZE / 2;

	ball_switch_position = ball_relative_position * 5 / ENEMY_PADDLE_LENGTH;

	switch (ball_switch_position) {
		case 0:
			ball_x_speed = -7;
			ball_y_speed = 3;
			break;
		case 1:
			ball_x_speed = -5;
			ball_y_speed = 5;
			break;
		case 2:
			ball_x_speed = (rand() % 3) - 1;
			ball_y_speed = 7;
			break;
		case 3:
			ball_x_speed = 5;
			ball_y_speed = 5;
			break;
		case 4:
			ball_x_speed = 7;
			ball_y_speed = 3;
			break;
	}

	ball_x_speed += (rand() % 3) - 1;
	ball_y_speed -= (rand() % 2) - 1;
}


uint8_t ball_detect_collision() {
	if (ball_x + ball_x_speed <= BOARD_MIN_X) {	// LEFT WALL
		return 1;
	} else if (ball_x + ball_x_speed + BALL_SIZE >= BOARD_MAX_X) { // RIGHT WALL
		return 3;
	} else if (ball_y + ball_y_speed < BOARD_MIN_Y) { // UPPER WALL
		return 2;
	} else if (ball_y + ball_y_speed + BALL_SIZE >= BOARD_MAX_Y) { // LOWER WALL
		return 4;
	} else if (ball_y + ball_y_speed + BALL_SIZE >= PADDLE_Y  && ball_y + ball_y_speed <= PADDLE_Y + PADDLE_THICKNESS) {
		if (ball_x + BALL_SIZE >= paddle_x && ball_x <= paddle_x + PADDLE_LENGTH) { // PADDLE
			if (ball_y_speed > 0) // Bounce only if the ball is falling
				return 5;
		}
	} else if (ball_y + ball_y_speed <= ENEMY_PADDLE_Y + ENEMY_PADDLE_THICKNESS  && ball_y + ball_y_speed + BALL_SIZE >= ENEMY_PADDLE_Y) {
		if (ball_x + BALL_SIZE >= enemy_paddle_x && ball_x <= enemy_paddle_x + ENEMY_PADDLE_LENGTH) { // ENEMY PADDLE
			if (ball_y_speed < 0) // Bounce only if the ball is rising
				return 6;
		}
	}
	return 0;
}

/* Collision_wall: parameter that specify the wall that is being collided
*		1: left wall
*		2: upper wall
*		3: right wall
*		4: lower wall
*		5: paddle hit
*		6: enemy paddle hit
*/
void ball_handle_collision(uint8_t collision_wall) {
	if (collision_wall == 1 || collision_wall == 3) {
		ball_x_speed = -ball_x_speed;
		pong_play_sound_wall();
	} else if (collision_wall == 2) {
		BUFFER_FULL_FLAG = 0;
		pong_increase_score();
		pong_scored_point();
	} else if (collision_wall == 4) {
		BUFFER_FULL_FLAG = 0;
		pong_increase_enemy_score();
		pong_scored_point();
	} else if (collision_wall == 5) {
		ball_handle_paddle_collision();
		pong_play_sound_paddle();
	} else if (collision_wall == 6) {
		ball_handle_enemy_paddle_collision();
		pong_play_sound_paddle();
	}
	return;
}


uint8_t ball_detect_reserved_board_zone() {
	// IF BALL IS IN SCORE ZONE
	if (ball_y + ball_y_speed + BALL_SIZE >= SCORE_Y - 5 && ball_y + ball_y_speed <= SCORE_MAX_Y &&
        ball_x + ball_x_speed + BALL_SIZE >= SCORE_X - 5 && ball_x + ball_x_speed <= SCORE_MAX_X)
		return 1;

	// IF BALL IS IN ENEMY SCORE ZONE
	if (ball_y + ball_y_speed + BALL_SIZE >= ENEMY_SCORE_Y - 5 && ball_y + ball_y_speed <= ENEMY_SCORE_MAX_Y &&
		ball_x + ball_x_speed + BALL_SIZE >= ENEMY_SCORE_X - 5 && ball_x + ball_x_speed <= ENEMY_SCORE_MAX_X)
		return 1;
	
	// IF BALL IS IN PADDLE ZONE
	if (ball_y + ball_y_speed + BALL_SIZE >= PADDLE_Y - 1 && ball_y + ball_y_speed <= PADDLE_Y + PADDLE_THICKNESS &&
		ball_x + ball_x_speed + BALL_SIZE > paddle_x && ball_x + ball_x_speed <= paddle_x + PADDLE_LENGTH) {
		return 1;
	}

	// IF BALL IS IN ENEMY PADDLE ZONE
	if (ball_y + ball_y_speed <= ENEMY_PADDLE_Y + ENEMY_PADDLE_THICKNESS + 2 && ball_y + ball_y_speed + BALL_SIZE >= ENEMY_PADDLE_Y &&
		ball_x + ball_x_speed + BALL_SIZE > enemy_paddle_x && ball_x + ball_x_speed <= enemy_paddle_x + ENEMY_PADDLE_LENGTH) {
		return 1;
	}
	return 0;
}


void ball_draw() {
	int x, y, i, j;
	uint8_t RESERVED_ZONE = ball_detect_reserved_board_zone();
	if (RESERVED_ZONE)
		BUFFER_FULL_FLAG = 1;
	for (x = ball_x, i = 0; x < ball_x + BALL_SIZE; x++, i++)
		for (y = ball_y, j = 0; y < ball_y + BALL_SIZE; y++, j++) {
			if (RESERVED_ZONE)
				ball_background_buffer_matrix[i][j] = LCD_GetPointCustom(x, y);	// Save background before drawing ball in case of reserved zone
			LCD_SetPoint(x, y, BALL_COLOR);
		}
}


void ball_delete() {
	int x, y, i, j;
	for (x = ball_x, i = 0; x < ball_x + BALL_SIZE; x++, i++)
		for (y = ball_y, j = 0; y < ball_y + BALL_SIZE; y++, j++) {
			if (!BUFFER_FULL_FLAG)
				LCD_SetPoint(x, y, BOARD_BACKGROUND_COLOR);
			else {
				LCD_SetPoint(x, y, ball_background_buffer_matrix[i][j]);
			}
		}
	BUFFER_FULL_FLAG = 0;
}


void ball_move() {
	uint8_t collision_wall;

	ball_delete();
	
	collision_wall = ball_detect_collision();
	if (collision_wall) {
		ball_handle_collision(collision_wall);
		if (collision_wall == 4) // GAME_LOST
			return;
	}	
	
	ball_x += ball_x_speed;
	ball_y += ball_y_speed;
	ball_draw();
	
}
