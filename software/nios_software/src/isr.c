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
void capture_isr(){
	OSIntEnter();
	*(EFFECT_ptr + 0) = 0x00000001;
	printf("Hemos recibido una foto\n");
	OSMboxPost(saveimg, (void *)1);
	OSIntExit();
}


void pushbutton_isr() {

	OSIntEnter();
	KEY_value = *(KEY_ptr + 3);

	*(KEY_ptr + 3) = 0;  //Borrar interrupcion
	if (KEY_value & 0x2)  //Derecha
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
		switch (effect%9){
			case 0:
				printf("Chroma\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000001;  // Efecto: Chroma Key
				*(EFFECT_ptr + 2) = 0x780038E7;  // Chroma Key: H: color_key; L: color_mask
				*(EFFECT_ptr + 3) = 0x00000000;  // Chroma Key: L: color_substitute
				break;
			case 1:
				printf("Eliminar R\n");
				*(EFFECT_ptr + 0) = 0x00000003;  // no usado
				*(EFFECT_ptr + 1) = 0x00000102;  // Efecto: Eliminación de colores RGB. delete_rgb=1; elimina R
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 2:
				printf("Eliminar G\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000202;  // Efecto: Eliminación de colores RGB. delete_rgb=1; elimina R
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 3:
				printf("Eliminar B\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000302;  // Efecto: Eliminación de colores RGB. delete_rgb=1; elimina R
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 4:
				printf("Blanco y negro\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00000004;  // Efecto: Escala de grises
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 5:
				printf("Cuantificacion 1\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00010008;  // Efecto: Cuantificación. cuantif_level=1;
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 6:
				printf("Cuantificacion 2\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00020008;  // Efecto: Cuantificación. cuantif_level=2;
				*(EFFECT_ptr + 2) = 0x00000000;  // no usado
				*(EFFECT_ptr + 3) = 0x00000000;  // no usado
				break;
			case 7:
				printf("Cuantificacion 3\n");
				*(EFFECT_ptr + 0) = 0x00000000;  // no usado
				*(EFFECT_ptr + 1) = 0x00030008;  // Efecto: Cuantificación. cuantif_level=3; (max)
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



