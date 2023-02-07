#include "..\inc\isr.h"
#include <includes.h>
#include "../inc/app_config.h"
#include "../inc/task_config.h"
#include <stdio.h>
#include "sys/alt_irq.h"

/**
 * Subrutina de manejo de interrupcion por pulsador incrustada en uCOS
 */
void pushbutton_isr() {
OSIntEnter();
	*(KEY_ptr + 3)=0;
	int KEY_value, SW_value;

	KEY_value = *(KEY_ptr + 3);		// Leemos registro de pulsadores
	SW_value = *(SW_switch_ptr);	// Leemos registro de Switches
	SW_value = SW_value & 1;
	printf("Despertando a Tarea sdcard\n");

	//Indicaremos a la funcion de sd que cargue una imagen posteando en su mailbox
	OSMboxPost(getimg, (void *)SW_value);
OSIntExit();
}



