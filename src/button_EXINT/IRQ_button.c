#include "button.h"
#include "lpc17xx.h"

#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */

extern uint8_t button_pressed;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	button_pressed = 0;
	reset_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	button_pressed = 1;
	reset_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	button_pressed = 2;
	reset_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}
