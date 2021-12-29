#include "GLCD_Extended.h"

void draw_thic_line_vertical(uint16_t x, uint16_t y0, uint16_t y1, uint16_t thickness, uint16_t color) {
	int i;
	for (i = x; i < x + thickness; i++)
		LCD_DrawLine(i, y0, i, y1, color);
}

void draw_thic_line_orizontal(uint16_t x0, uint16_t x1, uint16_t y, uint16_t thickness, uint16_t color) {
	int i;
	for (i = y; i < y + thickness; i++)
		LCD_DrawLine(x0, i, x1, i, color);
}
