#include "Pong.h"
#include "../Board/board.h"
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"
#include <stdlib.h>
#include <time.h>

int GAME_ON;
int GAME_LOST;
int GAME_PAUSED;


void pong_main_menu() {	
	LCD_Clear(Black);
	GUI_Text(100, 80, (uint8_t *) "PONG", White, Black);
	GUI_Text(40, 120, (uint8_t *) "Press KEY1 to start", White, Black);
}

void pong_initialize_game() {
	initialize_ball();
	draw_initial_game_board();
	//srand(time(NULL));
	GAME_ON = 1;
}

void pong_main_game_cycle() {
	//while (1) {
	//	move_paddle_absolute_position(190);
	//	move_paddle_absolute_position(5);
	//}
}

void pong_game_lost() {
	char str[] = "You lose!";
	GUI_Text(GAME_LOST_STRING_X, GAME_LOST_STRING_Y, (uint8_t *) str, White, Black);
	GAME_ON = 0;
	GAME_LOST = 1;
}
