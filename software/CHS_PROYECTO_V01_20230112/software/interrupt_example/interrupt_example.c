#include "key_codes.h"	// define los valores para KEY1, KEY2, KEY3
#include "system.h"
#include "sys/alt_irq.h"
#include <stdio.h> //Necesario para el NULL

void interval_timer_isr( );
void pushbutton_ISR( );

volatile int key_pressed = KEY2;
volatile int pattern = 0x0000000F;	// patr�n para display HEX

int main(void)
{
	volatile int * interval_timer_ptr = (int *) TIMER_BASE;	// Direcci�n Temporizador
	volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;					// Direcci�n pulsadores KEY
	volatile int * HEX3_HEX0_ptr	= (int *) HEX3_HEX0_BASE;	// Direcci�n HEX3_HEX0
	volatile int * HEX7_HEX4_ptr	= (int *) HEX7_HEX4_BASE;	// Direcci�n HEX7_HEX4

	int counter = 50000000;				// 1/(50 MHz) x (0x2625a0) = 50 msec
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	/* comienza el timer y habilita las interrupciones */
	*(interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	alt_irq_register(TIMER_IRQ, NULL, interval_timer_isr);
	
	*(KEY_ptr + 2) = 0xE; 		/* Mascara de los pulsadores (bit 0 es reset) */
	*(KEY_ptr + 3) = 0;
	alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_ISR);

	while(1){
		*(HEX3_HEX0_ptr) = pattern;				// Visualiza el patr�n en HEX3 ... HEX0
		*(HEX7_HEX4_ptr) = pattern;				// Visualiza el patr�n en HEX7 ... HEX4
	}
}
