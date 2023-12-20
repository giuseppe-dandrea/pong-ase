/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../EnemyPaddle/enemyPaddle.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

extern uint16_t sound_duration;

void TIMER0_IRQHandler (void)
{
	static int count = 0;
	static int ticks=0;
	if (count == 0)
		count = sound_duration;
	if (count > 0) {
		/* DAC management */	
		LPC_DAC->DACR = SinTable[ticks]<<6;
		ticks++;
		if(ticks==45) ticks=0;
		count--;
		if (count == 0)
			disable_timer(0);
	}

	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

extern int GAME_ON, GAME_LOST, GAME_PAUSED, GAME_RESET;


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if (GAME_ON) {
		disable_timer(1);
		reset_timer(1);
		enemy_paddle_find_next_position();
		enemy_paddle_move_one_step();
		enable_timer(1);
	}
	
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
