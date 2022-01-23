/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
**--------------------------------------------------------------------------------------------------------
** Modified by:              Giuseppe D'Andrea
** Modified date:            23/01/2022
** Version:                 v3.1
** Descriptions:            Pong multiplayer
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "Pong/Pong.h"
#include "RIT/RIT.h"
#include "ADC/adc.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

uint8_t button_pressed = 4;
int INIT_RAND_SEED;

void init_rand_seed() {
	INIT_RAND_SEED = 1;
	ADC_start_conversion();
	INIT_RAND_SEED = 0;
}

int main(void)
{
;	SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();												/* BUTTON Initialization              */
	LCD_Initialization();
	ADC_init();
	init_rand_seed();
	pong_initialize_game();	
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       */
	init_timer(1, 0x003C4B40);
	enable_RIT();
	enable_timer(1);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);	
	
	while (1)	
	{
		__ASM("wfi");
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
