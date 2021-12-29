#ifndef _GLCD_EXTENDED_H_
#define _GLCD_EXTENDED_H_

#include "LPC17xx.h"
#include "../GLCD/GLCD.h"

void draw_thic_line_vertical(uint16_t x, uint16_t y0, uint16_t y1, uint16_t thickness, uint16_t color);
void draw_thic_line_orizontal(uint16_t x0, uint16_t x1, uint16_t y, uint16_t thickness, uint16_t color);


#endif
