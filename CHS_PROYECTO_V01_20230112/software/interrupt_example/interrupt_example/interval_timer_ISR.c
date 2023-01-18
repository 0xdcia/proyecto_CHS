#include "key_codes.h" 	// define los valores de KEY1, KEY2, KEY3
#include "system.h"
#include "sys/alt_irq.h"

extern volatile int key_pressed;
extern volatile int pattern;

void interval_timer_isr( )
{
	volatile int * interval_timer_ptr = (int *) TIMER_BASE;

	*(interval_timer_ptr) = 0; 				// Borra la interrución

	/* Gira el patrón mostrado en los displays HEX  */
	if (key_pressed == KEY2)					// si KEY2 gira a la izquierda
		if (pattern & 0x80000000)
			pattern = (pattern << 1) | 1;	
		else
			pattern = pattern << 1;			
	else if (key_pressed == KEY1)				// si KEY1 gira a la derecha
		if (pattern & 0x00000001)			
			pattern = (pattern >> 1) | 0x80000000;
		else
			pattern = (pattern >> 1) & 0x7FFFFFFF;

	return;
}

