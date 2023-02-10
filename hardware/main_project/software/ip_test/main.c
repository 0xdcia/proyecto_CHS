/*
 * main.c
 *
 *  Created on: 6 de feb. de 2023
 *      Author: jdelpin
 */



#include <stdio.h>
#include "io.h"
#include "system.h"

#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"



// Defines para los pulsadores
#define KEY1 1
#define KEY2 2
#define KEY3 3



volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;  // addr pulsadores KEY

volatile int * EFFECT_ptr = (int * ) VIDEO_EFFECTS_BASE;  // addr EFFECTS


int effect_counter = 0;

/* Rutina de interrupción de los pulsadores.
 */


void capture_isr(){
	*(EFFECT_ptr + 0) = 0x00000001;
	printf("Interrupción recibida y deshabilitada.\n");
}



void pushbutton_isr()
{

	int KEY_value = *(KEY_ptr + 3);

	*(KEY_ptr + 3) = 0;  //Borrar interrupcion

	alt_printf("Interrumpido: ");
	effect_counter++;

	if (KEY_value & 0x8)  //Izquierda
	{
		alt_printf("Izquierda\n");
		switch(effect_counter % 9)
		{
			case 0:
				alt_printf("SDCard\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000001;  // Efecto: Cambiar a SDCard
				*(EFFECT_ptr + 2) = 0x00000000;  // Chroma Key: H: color_key; L: color_mask
				*(EFFECT_ptr + 3) = 0x00000000;  // Chroma Key: L: color_substitute
				break;

			case 1:
				alt_printf("Chroma\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000002;  // Efecto: Chroma Key
				*(EFFECT_ptr + 2) = 0xFFFF003F;  // Chroma Key: H: color_key=white; L: color_threshold=3F
				*(EFFECT_ptr + 3) = 0x00000000;  // Chroma Key: L: color_substitute
				break;

			case 2:
				alt_printf("Escala de grises\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000004;  // Efecto: Escala de grises
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			case 3:
				alt_printf("Cuantificación, level=1\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00010008;  // Efecto: Cuantif, level=1 : 4 bits por color
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			case 4:
				alt_printf("Cuantificación, level=2\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00020008;  // Efecto: Cuantif, level=2 : 3 bits por color
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			case 5:
				alt_printf("Cuantificación, level=3\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00030008;  // Efecto: Cuantif, level=3 : 2 bits por color
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			case 6:
				alt_printf("Negativo\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000010;  // Efecto: Negativo
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			case 7:
				alt_printf("Efectos simultáneos\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x0002001C;  // Efectos simultáneos: Blanco y negro, cuantif. level=2, negativo
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;

			default:
				alt_printf("Pausa de captura.\n");
				*(EFFECT_ptr + 0) = 0x00000003;  // Pause request e interrupt
				*(EFFECT_ptr + 1) = 0x00000000;  // Efecto: Ninguno
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
		}
	}
}




/*	if (press & 0x1) {  // Se ha pulsado el KEY0 (0001)
		alt_printf("Chroma key\n");

		*(EFFECT_ptr + 0) = 0x00000000;  // no usado
		*(EFFECT_ptr + 1) = 0x00000001;  // Efecto: Chroma Key
		*(EFFECT_ptr + 2) = 0x00000000;  // Chroma Key: H: color_key; L: color_mask
		*(EFFECT_ptr + 3) = 0x00000000;  // Chroma Key: L: color_substitute

		IOWR_32DIRECT(EFFECT_ptr, 0, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 1, 0x00000001);
		IOWR_32DIRECT(EFFECT_ptr, 2, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 3, 0x00000000);
	}
	if (press & 0x2) {  // Se ha pulsado el KEY1 (0010)
		alt_printf("Eliminación RGB\n");

		*(EFFECT_ptr + 0) = 0x00000000;  // no usado
		*(EFFECT_ptr + 1) = 0x00000102;  // Efecto: Eliminación de colores RGB. delete_rgb=1; elimina R
		*(EFFECT_ptr + 2) = 0x00000000;  // no usado
		*(EFFECT_ptr + 3) = 0x00000000;  // no usado

		IOWR_32DIRECT(EFFECT_ptr, 0, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 1, 0x00000102);
		IOWR_32DIRECT(EFFECT_ptr, 2, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 3, 0x00000000);
	}
	if (press & 0x4) {  // Se ha pulsado el KEY2 (0100)
		alt_printf("Blanco y negro\n");

		*(EFFECT_ptr + 0) = 0x00000000;  // no usado
		*(EFFECT_ptr + 1) = 0x00000004;  // Efecto: Escala de grises
		*(EFFECT_ptr + 2) = 0x00000000;  // no usado
		*(EFFECT_ptr + 3) = 0x00000000;  // no usado

		IOWR_32DIRECT(EFFECT_ptr, 0, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 1, 0x00000004);
		IOWR_32DIRECT(EFFECT_ptr, 2, 0x00000000);
		IOWR_32DIRECT(EFFECT_ptr, 3, 0x00000000);

		reg_value = *(EFFECT_ptr + 1);

		alt_printf("valor_registro1: %d\n", reg_value);
	}
	if (press & 0x8) {  // Se ha pulsado el KEY3 (1000)
		alt_printf("Cuantificación\n");

		*(EFFECT_ptr + 0) = 0x00000000;  // no usado
		*(EFFECT_ptr + 1) = 0x00030008;  // Efecto: Cuantificación. cuantif_level=3; (max)
		*(EFFECT_ptr + 2) = 0x00000000;  // no usado
		*(EFFECT_ptr + 3) = 0x00000000;  // no usado
*/



/* Función principal
 */
int main(void)
{
	// Pulsadores
	*(KEY_ptr + 2) = 0xE;  	// Máscara de los pulsadores (keys 3210: 1110) (el 0 es reset)
	*(KEY_ptr + 3) = 0;		// Registro de los pulsadores a cero

	alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_isr);  // Habilitar int. pulsadores

	alt_irq_register(VIDEO_EFFECTS_IRQ, NULL, capture_isr);  // Habilitar int. video_effects

	*(EFFECT_ptr + 0) = 0x0;  // Reset de registros
	*(EFFECT_ptr + 1) = 0x0;
	*(EFFECT_ptr + 2) = 0x0;
	*(EFFECT_ptr + 3) = 0x0;

	alt_printf("Main finish\n");

	while (1) {}
}



