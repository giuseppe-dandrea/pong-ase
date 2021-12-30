/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../Paddle/paddle.h"
#include "../Ball/ball.h"
#include "../ADC/adc.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern int GAME_ON, GAME_LOST, GAME_PAUSED;

void button1_handler (void)
{
}

void button2_handler (void)
{
}

void button3_handler (void)
{
}

void pong_ball_handler (void) {
	move_ball();
}

extern uint8_t button_pressed;
uint8_t button_pin;
void (*button_handlers[]) (void) = {&button1_handler, &button2_handler, &button3_handler};

void RIT_IRQHandler (void)
{	
	static int down = 0;
	if (button_pressed == 4 && GAME_ON) { // Dummy value to manage game cycle instead of buttons
		disable_RIT();
		ADC_start_conversion();
		pong_ball_handler();
		move_paddle_one_step_to_next_x();
		reset_RIT();
		enable_RIT();
		return;
	} else if (button_pressed != 4) {
		down++;
		button_pin = 10 + button_pressed;
		if((LPC_GPIO2->FIOPIN & (1<<button_pin)) == 0){
			reset_RIT();
			if (down == 1)
				(*button_handlers[button_pressed]) ();
		}
		else {
			down=0;
			button_pressed = 4;
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << button_pin*2);     /* External interrupt 0 pin selection */
		}
		
	}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
