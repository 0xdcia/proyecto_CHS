/*
 * main.c
 *
 *  Created on: 6 de feb. de 2023
 *      Author: jdelpin
 */



#include <stdio.h>
#include "system.h"

#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"



// Defines para los pulsadores
#define KEY1 1
#define KEY2 2
#define KEY3 3



volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;  // addr pulsadores KEY

volatile int * EFFECT_ptr = (int * ) VIDEO_EFFECTS_BASE;  // addr EFFECTS


/* Rutina de interrupci�n de los pulsadores.
 */
void pushbutton_isr( )
{
	int press;

	alt_printf("Efectivamente me he interrumpido\n");

	press = *(KEY_ptr + 3);  // Lee el registro de los pulsadores
	*(KEY_ptr + 3) = 0;  // Elimina la interrupci�n

	if (press & 0x1) {  // Se ha pulsado el KEY2 (0100)
		*(EFFECT_ptr + 1) = 0x1;
	}
	if (press & 0x2) {  // Se ha pulsado el KEY2 (0100)
		*(EFFECT_ptr + 1) = 0x2;
	}
	if (press & 0x4) {  // Se ha pulsado el KEY2 (0100)
		*(EFFECT_ptr + 1) = 0x4;
	}
	if (press & 0x8) {  // Se ha pulsado el KEY3 (1000)
		*(EFFECT_ptr + 1) = 0x10;
	}

	return;
}



/* Funci�n principal
 */
int main(void)
{
	// Pulsadores
	*(KEY_ptr + 2) = 0xE;  	// M�scara de los pulsadores (keys 3210: 1110) (el 0 es reset)
	*(KEY_ptr + 3) = 0;		// Registro de los pulsadores a cero

	alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_isr);  // Habilitar int. pulsadores

	*(EFFECT_ptr + 0) = 0x0;
	*(EFFECT_ptr + 1) = 0x0;
	*(EFFECT_ptr + 2) = 0x0;
	*(EFFECT_ptr + 3) = 0x0;

	alt_printf("Main finish\n");

	while (1) {}
}



