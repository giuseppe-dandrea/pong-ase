#include "Pong.h"
#include "../Board/board.h"
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../GLCD_Extended/GLCD_Extended.h"


void pong_main_menu() {	
	LCD_Clear(Black);
	GUI_Text(100, 80, (uint8_t *) "PONG", White, Black);
	GUI_Text(40, 120, (uint8_t *) "Press KEY1 to start", White, Black);
}

void pong_initialize_game() {
	initialize_ball();
	draw_initial_game_board();
}

void pong_main_game_cycle() {
	//while (1) {
	//	move_paddle_absolute_position(190);
	//	move_paddle_absolute_position(5);
	//}
}
