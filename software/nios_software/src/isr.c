#include "..\inc\isr.h"
#include "../inc/app_config.h"
#include "../inc/task_config.h"
#include <stdio.h>
#include "sys/alt_irq.h"
#include "..\inc\sdcard.h"
#include <io.h>

int KEY_value;
int toggle = 0;
int effect = 0;
/**
 * Subrutina de manejo de interrupcion por pulsador incrustada en uCOS
 */
int hist = 0;
int SW_value = 0;
void capture_isr(){//Se ha dibujado un frame completo
	OSIntEnter();
	*(EFFECT_ptr + 0) = 0x00000001;//Desactivar interrupcion - mantener pausa
	isSaving = true;
	printf("Hemos recibido una foto\n");
	if(hist == 0){//Se ha pedido una captura
		OSMboxPost(saveimg, (void *)1);
	}
	else {//Se ha pedido una pausa
		SW_value = *(SW_switch_ptr);
		if(SW_value & 0x4000){
			OSMboxPost(drawHist, (void *)1);
		}//El histograma está activo - tarea de dibujar histograma en overlay
	}
	hist = 0;
	OSIntExit();
}

unsigned int lastPressed = 0;
unsigned int threshold = 1000;
unsigned int aux;
void pushbutton_isr() {

	OSIntEnter();
	KEY_value = *(KEY_ptr + 3);

	*(KEY_ptr + 3) = 0;  //Borrar interrupcion
	if (KEY_value & 0x2)  //Derecha
	{
		image++;
		printf("Despertando a Tarea sdcard %d\n", KEY_value);
		//Indicaremos a la funcion de sd que cargue una imagen posteando en su mailbox
		OSMboxPost(getimg, (void *)1);
	}
	else if (KEY_value & 0x4){//Centro
		aux = OSTimeGet();
		if(lastPressed + threshold > aux){//Hacer una captura - doblo click
			*(EFFECT_ptr + 0) = 0x00000003;//Pausar video y capturar
		}
		else{//Pausa / reanudar video
			/*To-do: Proteger con Mutex, hasta que no acabe una captura no se puede quitar pausa
			 * No sera bloqueante, ignorar si se está capturando
			 * */
			if(!isSaving){
				if(toggle){//Pausar (y calcular histograma?)
					hist = 1;
					*(EFFECT_ptr + 0) = 0x00000003;
				}
				else{//Reanudar
					*(EFFECT_ptr + 0) = 0x00000000;
				}
				toggle = !toggle;
			}
		}
		lastPressed = aux;
	}
	else//Izquierda
	{
		if(image > 0){
			image--;
		}
		else{
			image = num_imgs - 1;
		}
		OSMboxPost(getimg, (void *)1);
	}

OSIntExit();
}



