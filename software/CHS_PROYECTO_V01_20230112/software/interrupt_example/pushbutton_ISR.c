#include "key_codes.h" 	// define los valores de KEY1, KEY2, KEY3
#include "system.h"
#include "sys/alt_irq.h"

extern volatile int key_pressed;
extern volatile int pattern;

void pushbutton_ISR( )
{
	volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;
  	volatile int * slider_switch_ptr = (int *) SWITCHES_BASE;
	int press;

	press = *(KEY_ptr + 3);					// lee el registro de los pulsadores
	*(KEY_ptr + 3) = 0; 					// borra la interrupción

	if (press & 0x2)						// KEY1
		key_pressed = KEY1;
	else if (press & 0x4)					// KEY2
		key_pressed = KEY2;
	else 									// press & 0x8, lo que significa KEY3
		pattern = *(slider_switch_ptr); 	//Lee los interruptores

	return;
}
