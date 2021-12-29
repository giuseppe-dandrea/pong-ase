#include "ball.h"
#include "../Board/board.h"
#include "../Paddle/paddle.h"
#include "../GLCD/GLCD.h"
#include <stdlib.h>

uint16_t ball_x = 5;
uint16_t ball_y = 10;
int16_t ball_x_speed = 5;
int16_t ball_y_speed = 5;
const uint16_t ball_size = 5;
const uint16_t ball_color = Green;

uint16_t **ball_background_buffer_matrix;
uint8_t BUFFER_FULL_FLAG = 0;

extern uint16_t paddle_x, paddle_y, paddle_length;

extern int score;
extern int best_score;
extern const int score_x;
extern const int score_y;
extern const int best_score_x;
extern const int best_score_y;
extern const int score_max_x;
extern const int score_max_y;
extern const int best_score_max_x;
extern const int best_score_max_y;


void initialize_ball() {
	int i;
	ball_background_buffer_matrix = (uint16_t**) malloc(ball_size * sizeof(uint16_t*));
	for (i = 0; i < ball_size; i++)
		ball_background_buffer_matrix[i] = (uint16_t*) malloc(ball_size * sizeof(uint16_t));

}

// TODO: GESTIRE CASO COLLISIONE CON SPIGOLO!!
uint8_t ball_detect_collision() {
	if (ball_x + ball_x_speed < board_min_x) {	// LEFT WALL
		return 1;
	} else if (ball_x + ball_x_speed + ball_size >= board_max_x) { // RIGHT WALL
		return 3;
	} else if (ball_y + ball_y_speed < board_min_y) { // UPPER WALL
		return 2;
	} else if (ball_y + ball_y_speed + ball_size >= board_max_y) { // LOWER WALL
		return 4;
	} else if (	ball_y + ball_y_speed + ball_size >= paddle_y ) {
		if ( ball_x + ball_size >= paddle_x && ball_x <= paddle_x + paddle_length) { // PADDLE
			return 5;
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
*/
void ball_handle_collision(uint8_t collision_wall) {
	if (collision_wall == 1 || collision_wall == 3)
		ball_x_speed = -ball_x_speed;
	else if (collision_wall == 2 || collision_wall == 4)
		ball_y_speed = -ball_y_speed;
	else if (collision_wall == 5) {
		ball_y_speed = -ball_y_speed;
		increase_score();
	}
	
	// BUFFER_FULL_FLAG = 0;
	
	return;
}


uint8_t ball_detect_reserved_board_zone() {
	// IF BALL IS IN SCORE ZONE
	if (ball_y + ball_y_speed + ball_size >= score_y && ball_y + ball_y_speed <= score_max_y &&
		ball_x + ball_x_speed + ball_size >= score_x && ball_x + ball_x_speed <= score_max_x)
		return 1;
	
	// IF BALL IS IN BEST SCORE ZONE
	if (ball_y + ball_y_speed + ball_size >= best_score_y && ball_y + ball_y_speed <= best_score_max_y &&
		ball_x + ball_x_speed + ball_size >= score_x && ball_x + ball_x_speed <= best_score_max_x)
		return 1;
	
	// IF BALL IS IN PADDLE ZONE
	if (ball_y + ball_y_speed + ball_size > paddle_y) {
		return 1;
	}
	return 0;
}


void draw_ball(uint16_t x0, uint16_t y0) {
	int x, y, i, j;
	uint8_t RESERVED_ZONE = ball_detect_reserved_board_zone();
	if (RESERVED_ZONE)
		BUFFER_FULL_FLAG = 1;
	for (x = x0, i = 0; x < x0 + ball_size; x++, i++)
		for (y = y0, j = 0; y < y0 + ball_size; y++, j++) {
			if (RESERVED_ZONE)
				ball_background_buffer_matrix[i][j] = LCD_GetPointCustom(x, y);	// Save background before drawing ball in case of reserved zone
			LCD_SetPoint(x, y, ball_color);
		}
}


void delete_ball() {
	int x, y, i, j;
	for (x = ball_x, i = 0; x < ball_x + ball_size; x++, i++)
		for (y = ball_y, j = 0; y < ball_y + ball_size; y++, j++) {
			if (!BUFFER_FULL_FLAG)
				LCD_SetPoint(x, y, board_background_color);
			else {
				LCD_SetPoint(x, y, ball_background_buffer_matrix[i][j]);
			}
		}
	BUFFER_FULL_FLAG = 0;
}


void move_ball() {
	uint8_t collision_wall;
	
	delete_ball();
	
	collision_wall = ball_detect_collision();
	if (collision_wall) {
		ball_handle_collision(collision_wall);
	}
	
	//ball_detect_reserved_board_zone();
	
	
	ball_x += ball_x_speed;
	ball_y += ball_y_speed;
	draw_ball(ball_x, ball_y);
	
}
