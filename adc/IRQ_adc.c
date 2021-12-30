/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../Paddle/paddle.h"
#include "../Board/board.h"
#include <stdlib.h>

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;
uint16_t potentiometer;
uint16_t potentiometer_tmp = BOARD_MIN_X;
uint16_t potentiometer_last = BOARD_MIN_X;		/* Last converted value               */

uint16_t map_potentiometer_to_x_pos(unsigned short potentiometer) {
	return ((BOARD_MAX_X - PADDLE_LENGTH - BORDER_THICKNESS) * potentiometer / 0xFFF) + BOARD_MIN_X;
}

void ADC_IRQHandler(void) {
	static int count = 0;
	uint16_t potentiometer_diff;
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
	if (count == 0)
		potentiometer = map_potentiometer_to_x_pos(AD_current);
	else {
		potentiometer_tmp = map_potentiometer_to_x_pos(AD_current);
		potentiometer_diff = abs(potentiometer - potentiometer_tmp);
		if (potentiometer_diff > 5) {
			count = 0;
			return;
		}
	}
	count++;

	if(potentiometer != potentiometer_last && count > 1){
		move_paddle_absolute_position(potentiometer);
		
		potentiometer_last = potentiometer;
		count = 0;
  }
}
