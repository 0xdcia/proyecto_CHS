#include "..\inc\isr.h"
#include <includes.h>
#include "../inc/app_config.h"
#include "../inc/task_config.h"
#include <stdio.h>
#include "sys/alt_irq.h"
#include "..\inc\sdcard.h"
#include <io.h>

int KEY_value, SW_value;
int toggle = 0;
int effect = 0;
/**
 * Subrutina de manejo de interrupcion por pulsador incrustada en uCOS
 */
void pushbutton_isr() {
OSIntEnter();
	KEY_value = *(KEY_ptr + 3);

	*(KEY_ptr + 3) = 0;//Borrar interrupcion
	if (KEY_value & 0x2)//Derecha
	{
		image++;
		printf("Despertando a Tarea sdcard %d, %d\n", KEY_value, SW_value);
		//Indicaremos a la funcion de sd que cargue una imagen posteando en su mailbox
		OSMboxPost(getimg, (void *)1);
	}
	else if (KEY_value & 0x4){
		if(toggle){
			IOWR_32DIRECT(MTL_PIXEL_BUFFER_DMA_BASE, 0, (SRAM_BASE + 0x080000000));
			IOWR_32DIRECT(MTL_PIXEL_BUFFER_DMA_BASE, 4, (SRAM_BASE + 0x080000000));
		}
		else{
			IOWR_32DIRECT(MTL_PIXEL_BUFFER_DMA_BASE, 0, (0x09100000));
			IOWR_32DIRECT(MTL_PIXEL_BUFFER_DMA_BASE, 4, (0x09100000));
		}
		toggle = !toggle;
	}
	else//Izquierda
	{
		switch (effect%5){
			case 0:
				printf("Chroma\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000001;  // Efecto: Chroma Key
				*(EFFECT_ptr + 2) = 0x00000000;  // Chroma Key: H: color_key; L: color_mask
				*(EFFECT_ptr + 3) = 0x00000000;  // Chroma Key: L: color_substitute
				break;
			case 1:
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000102;  // Efecto: Eliminaci�n de colores RGB. delete_rgb=1; elimina R
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 2:
				printf("Blanco y negro\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000004;  // Efecto: Escala de grises
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 3:
				printf("Cuantificacion\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00030008;  // Efecto: Cuantificaci�n. cuantif_level=3; (max)
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			default:
				printf("Invertir\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000010;  // Efecto: Cuantificaci�n. cuantif_level=3; (max)
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
		}
		effect++;
	}

	SW_value = *(SW_switch_ptr);	// Leemos registro de Switches
	SW_value = SW_value & 1;

OSIntExit();
}



