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
		if(image > 0) image--;
		else image = num_imgs-1;
		printf("Despertando a Tarea sdcard %d, %d\n", KEY_value, SW_value);
		//Indicaremos a la funcion de sd que cargue una imagen posteando en su mailbox
		OSMboxPost(getimg, (void *)1);
	}

	SW_value = *(SW_switch_ptr);	// Leemos registro de Switches
	SW_value = SW_value & 1;

OSIntExit();
}



