#include "..\inc\app_config.h"
#include "..\inc\isr.h"
#include "system.h"
#include <stdlib.h>
#include <includes.h>
#include <stdio.h>

/* Variables globales */
volatile int * red_LED_ptr = (int *) RED_LEDS_BASE;
volatile int * green_LED_ptr = (int *) GREEN_LEDS_BASE;
volatile int * HEX3_HEX0_ptr= (int *) HEX3_HEX0_BASE;
volatile int * HEX7_HEX4_ptr= (int *) HEX7_HEX4_BASE;
volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;
volatile int * SW_switch_ptr = (int *) SWITCHES_BASE;
volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;
volatile short * pixel_buffer= (short *) SRAM_BASE;	// MTL pixel buffer
volatile char * character_buffer= (char *)  MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE; // MTL character buffer

void Init_App(void){
	//Registrar interrupciones
	printf("Registrando interrupcion\n");
	*(KEY_ptr + 2) = 0xF;
	*(KEY_ptr + 3) = 0;
	alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_isr);
}
