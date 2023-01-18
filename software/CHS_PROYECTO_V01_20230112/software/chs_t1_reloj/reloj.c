/*
 * reloj.c
 *
 *  Created on: 21 de oct. de 2022
 *      Author: Juan Del Pino Mena
 *
 *      Co-dise�o hardware-software
 *
 *  TAREA 1: DISE�O DE UN RELOJ
 *
 *  Programa C preparado para correr en el NIOS II del SoPC de las pr�cticas.
 *
 */

#include <stdio.h>
#include "system.h"

#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"


// Defines para los pulsadores 
#define KEY1 1
#define KEY2 2
#define KEY3 3

// Defines para el dibujo en la pantalla MTL.

#define CLOCK_SEGMENT_WIDTH 7
#define CLOCK_SEGMENT_HEIGHT 25

#define CLOCK_DOTS_WIDTH 25 
#define CLOCK_DIGIT_WIDTH 50
#define CLOCK_DIGIT_HEIGHT 2 * CLOCK_SEGMENT_HEIGHT + 3 * CLOCK_SEGMENT_WIDTH  // 71 px
#define CLOCK_DIGIT_X_PADDING 5

#define CLOCK_DOTS_X_PADDING 8
#define CLOCK_DOTS_SIZE 7
#define CLOCK_DOTS_Y_HIGH 22
#define CLOCK_DOTS_Y_LOW 42

#define CLOCK_FIRST_DIGIT_X 25
#define CLOCK_FIRST_DIGIT_Y 85


/* Estructura para almacenar la hora actual de forma sencilla
 */
struct time_t{
	int hours;
	int minutes;
	int seconds;
};

/* Para la conversi�n de hexadecimal a 7 segmentos. 
 */
int hex7seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
				 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

int count = 0;  		// Cuenta del reloj, en segundos
struct time_t time;  	// Estructura de horas, minutos y segundos

volatile int * interval_timer_ptr = (int *) TIMER_BASE;		// addr Temporizador
volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;  		// addr pulsadores KEY
volatile int * slider_switch_ptr = (int *) SWITCHES_BASE;

volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE;	// addr HEX3_HEX0
volatile int * HEX7_HEX4_ptr = (int *) HEX7_HEX4_BASE;	// addr HEX7_HEX4
volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// addr 16x2 display

volatile int background_color = 0x0000;
volatile int background_color_8b = 0x00;
volatile int digit_color = 0xFFFF;
volatile int digit_color_8b = 0xFF;


/* Convierte el tiempo en segundos a la estructura time_t
 */
void seconds_to_time_t(int seconds, struct time_t* time)
{
	int resto;

	time->hours = seconds / 3600;
	resto = seconds % 3600;

	time->minutes = resto / 60;
	resto = resto % 60;

	time->seconds = resto;
}


/* Realiza la conversi�n de la estructura time_t a siete segmentos.
 * Y lo env�a por el registro correspondiente.
 */
void send_time_to_7seg(struct time_t* time)
{
	int pattern7_4 = 0x0000;  // Patr�n en HEX7 a HEX4
	int pattern3_1 = 0x0000;  // Patr�n en HEX3 a HEX0

	pattern7_4 = (hex7seg[time->hours / 10] << 24) | (hex7seg[time->hours % 10] << 16) |
				 (hex7seg[time->minutes / 10] << 8) | (hex7seg[time->minutes % 10]);
	pattern3_1 = (hex7seg[time->seconds / 10] << 24) | (hex7seg[time->seconds % 10] << 16);

	*(HEX3_HEX0_ptr) = pattern3_1;  // Copia del patr�n en HEX3 a HEX0
	*(HEX7_HEX4_ptr) = pattern7_4;  // Copia del patr�n en HEX7 a HEX4
}


/* Rutina para mover el cursor de la LCD
 */
void LCD_cursor(int x, int y)
{
  	char instruction = x;
	if (y != 0) instruction |= 0x40;	// set bit 6 for bottom row
	instruction |= 0x80;				// need to set bit 7 to set the cursor location
	*(LCD_display_ptr) = instruction;	// write to the LCD instruction register
}


/* Rutina encargada de enviar un string a la LCD
 */
void LCD_text(char * text_ptr)
{
	while ( *(text_ptr) )
	{
		*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		++text_ptr;
	}
}


/* Rutina para apagar el cursor de la LCD
 */
void LCD_cursor_off(void)
{
  	*(LCD_display_ptr) = 0x0C;	// turn off the LCD cursor
}


/* Escribe la hora en la primera l�nea del LCD de 16x2 caracteres
 */
void send_time_to_lcd_1602(struct time_t* time)
{
	char reloj_txt[40] = "";

	sprintf(reloj_txt, "    %02d:%02d:%02d    ", time->hours, time->minutes, time->seconds);

	LCD_cursor(0,0);			// set LCD cursor location to top row
	LCD_text(reloj_txt);
	LCD_cursor_off();			// turn off the LCD cursor
}


void MTL_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;
	int SRAM_BASE_SIN_CACHE = (SRAM_BASE + 0x080000000);  //Activando el bit m�s significativo se elude la cache de datos
  	volatile short * pixel_buffer = (short *) SRAM_BASE_SIN_CACHE;	// MTL pixel buffer

  	/* se asume que las coordenadas del rectangulo son correctas */
	for (row = y1; row <= y2; row++)
	{
		col = x1;
		while (col <= x2)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;	//procesa mitad direcciones
			++col;
		}
	}
}


void MTL_fill_screen(int color) {
	MTL_box(0, 0, 399, 239,	color);
}


/* Dibuja los dos puntos en la coordenada seleccionada
 * NO UTILIZADA
 */
void draw_clock_dots_dma(int x, int y)
{

}


/* Dibuja los dos puntos en la coordenada seleccionada
 */
void draw_clock_dots(int x, int y)
{
	MTL_box(  // Punto superior
		x + CLOCK_DOTS_X_PADDING,
		y + CLOCK_DOTS_Y_HIGH,
		x + CLOCK_DOTS_X_PADDING + CLOCK_DOTS_SIZE,
		y + CLOCK_DOTS_Y_HIGH + CLOCK_DOTS_SIZE,
		digit_color);

	MTL_box(  // Punto inferior
		x + CLOCK_DOTS_X_PADDING,
		y + CLOCK_DOTS_Y_LOW,
		x + CLOCK_DOTS_X_PADDING + CLOCK_DOTS_SIZE,
		y + CLOCK_DOTS_Y_LOW + CLOCK_DOTS_SIZE,
		digit_color);
}


/* Dibuja el d�gito de reloj dado en las coordenadas especificadas.
 * El formato de paso los d�gitos es igual al de un display de 7 segmentos real
 * NO UTILIZADA
 */
void draw_clock_digit_dma(int code, int x, int y,
					  alt_up_pixel_buffer_dma_dev *pixel_buffer_dev)
{
	// Formato: pixel_buffer, x0, y0, x1, y1, color, backbuffer

	/* &: operaci�n AND l�gica. Si el bit correspondiente del 7 segmentos hay que
	encenderlo, su correspondiente if ser� true y dibuja el segmento. */

	if (code & 0x01) {  // Si se debe encender el segmento A
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING,
			y,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + CLOCK_SEGMENT_WIDTH,
			digit_color, 0);
	}
	if (code & 0x02) {  // Si se debe encender el segmento B
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + CLOCK_SEGMENT_WIDTH,
			x + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color, 0);
	}
	if (code & 0x04) {  // Si se debe encender el segmento C
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			x + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + 2 * CLOCK_SEGMENT_WIDTH + 2 * CLOCK_SEGMENT_HEIGHT,
			digit_color, 0);
	}
	if (code & 0x08) {  // Si se debe encender el segmento D
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING,
			y + 2 * CLOCK_SEGMENT_HEIGHT + 2 * CLOCK_SEGMENT_WIDTH,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + 2 * CLOCK_SEGMENT_HEIGHT + 3 * CLOCK_SEGMENT_WIDTH,
			digit_color, 0);
	}
	if (code & 0x10) {  // Si se debe encender el segmento E
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_DIGIT_X_PADDING,
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING,
			y + 2 * CLOCK_SEGMENT_WIDTH + 2 * CLOCK_SEGMENT_HEIGHT,
			digit_color, 0);
	}
	if (code & 0x20) {  // Si se debe encender el segmento F
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_DIGIT_X_PADDING,
			y + CLOCK_SEGMENT_WIDTH,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING,
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color, 0);
	}
	if (code & 0x40) {  // Si se debe encender el segmento G
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING,
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT,
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color, 0);
	}
}


/* Dibuja el d�gito de reloj dado en las coordenadas especificadas.
 * El formato de paso los d�gitos es igual al de un display de 7 segmentos real
 */
void draw_clock_digit(int code, int x, int y)
{	
	// Formato: pixel_buffer, x0, y0, x1, y1, color, backbuffer

	/* &: operaci�n AND l�gica. Si el bit correspondiente del 7 segmentos hay que 
	encenderlo, su correspondiente if ser� true y dibuja el segmento. */

	if (code & 0x01) {  // Si se debe encender el segmento A
		MTL_box(
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING, 
			y, 
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + CLOCK_SEGMENT_WIDTH,
			digit_color);
	}
	if (code & 0x02) {  // Si se debe encender el segmento B
		MTL_box(
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + CLOCK_SEGMENT_WIDTH, 
			x + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color);
	}
	if (code & 0x04) {  // Si se debe encender el segmento C
		MTL_box(
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT, 
			x + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + 2 * CLOCK_SEGMENT_WIDTH + 2 * CLOCK_SEGMENT_HEIGHT,
			digit_color);
	}
	if (code & 0x08) {  // Si se debe encender el segmento D
		MTL_box(
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING, 
			y + 2 * CLOCK_SEGMENT_HEIGHT + 2 * CLOCK_SEGMENT_WIDTH, 
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + 2 * CLOCK_SEGMENT_HEIGHT + 3 * CLOCK_SEGMENT_WIDTH,
			digit_color);
	}
	if (code & 0x10) {  // Si se debe encender el segmento E
		MTL_box(
			x + CLOCK_DIGIT_X_PADDING, 
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT, 
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING, 
			y + 2 * CLOCK_SEGMENT_WIDTH + 2 * CLOCK_SEGMENT_HEIGHT,
			digit_color);
	}
	if (code & 0x20) {  // Si se debe encender el segmento F
		MTL_box(
			x + CLOCK_DIGIT_X_PADDING, 
			y + CLOCK_SEGMENT_WIDTH, 
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING, 
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color);
	}
	if (code & 0x40) {  // Si se debe encender el segmento G
		MTL_box(
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING, 
			y + CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT, 
			x + CLOCK_SEGMENT_WIDTH + CLOCK_DIGIT_X_PADDING + CLOCK_SEGMENT_HEIGHT, 
			y + 2 * CLOCK_SEGMENT_WIDTH + CLOCK_SEGMENT_HEIGHT,
			digit_color);
	}
}


/* Funci�n encargada de dibujar el reloj en la pantalla MTL.
 * NO UTILIZADA
 */
void draw_clock_dma(struct time_t * time, alt_up_pixel_buffer_dma_dev *pixel_buffer_dev)
{
	int digit_codes[] = {hex7seg[time->hours / 10], hex7seg[time->hours % 10],
						 hex7seg[time->minutes / 10], hex7seg[time->minutes % 10],
						 hex7seg[time->seconds / 10], hex7seg[time->seconds % 10]};

	// posici�n en la que se va a dibujar el d�gito (coordenada superior izquierda)
	// int x[] = {CLOCK_FIRST_DIGIT_X,
	//            CLOCK_FIRST_DIGIT_X + 1 * CLOCK_DIGIT_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 2 * CLOCK_DIGIT_WIDTH + 1 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 3 * CLOCK_DIGIT_WIDTH + 1 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 4 * CLOCK_DIGIT_WIDTH + 2 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 5 * CLOCK_DIGIT_WIDTH + 2 * CLOCK_DOTS_WIDTH}

	int x = 0;
	int y = CLOCK_FIRST_DIGIT_Y;

	// dibuja los seis d�gitos
	for (int i = 0; i < 6; i++)
	{
		x = CLOCK_FIRST_DIGIT_X + i * CLOCK_DIGIT_WIDTH + (i/2) * CLOCK_DOTS_WIDTH;
		draw_clock_digit_dma(digit_codes[i], x, y, pixel_buffer_dev);
	}

	// dibuja los dos pares de puntos
	// x = CLOCK_FIRST_DIGIT_X + 2 * CLOCK_DIGIT_WIDTH;
	// draw_clock_dots(x, y);
	// x = CLOCK_FIRST_DIGIT_X + 4 * CLOCK_DIGIT_WIDTH + CLOCK_DOTS_WIDTH;
	// draw_clock_dots(x, y);
}


void draw_clock(struct time_t * time)
{
	int digit_codes[] = {hex7seg[time->hours / 10], hex7seg[time->hours % 10],
						 hex7seg[time->minutes / 10], hex7seg[time->minutes % 10],
						 hex7seg[time->seconds / 10], hex7seg[time->seconds % 10]};

	// posici�n en la que se va a dibujar el d�gito (coordenada superior izquierda)
	// int x[] = {CLOCK_FIRST_DIGIT_X,
	//            CLOCK_FIRST_DIGIT_X + 1 * CLOCK_DIGIT_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 2 * CLOCK_DIGIT_WIDTH + 1 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 3 * CLOCK_DIGIT_WIDTH + 1 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 4 * CLOCK_DIGIT_WIDTH + 2 * CLOCK_DOTS_WIDTH,
	// 		   CLOCK_FIRST_DIGIT_X + 5 * CLOCK_DIGIT_WIDTH + 2 * CLOCK_DOTS_WIDTH}

	int x = 0;
	int y = CLOCK_FIRST_DIGIT_Y;

	MTL_box(CLOCK_FIRST_DIGIT_X, CLOCK_FIRST_DIGIT_Y,
			399-CLOCK_FIRST_DIGIT_X, CLOCK_FIRST_DIGIT_Y + CLOCK_DIGIT_HEIGHT,
			background_color);

	// dibuja los seis d�gitos
	for (int i = 0; i < 6; i++)
	{
		x = CLOCK_FIRST_DIGIT_X + i * CLOCK_DIGIT_WIDTH + (i/2) * CLOCK_DOTS_WIDTH;
		draw_clock_digit(digit_codes[i], x, y);
	}

	// dibuja los dos pares de puntos
	x = CLOCK_FIRST_DIGIT_X + 2 * CLOCK_DIGIT_WIDTH;
	draw_clock_dots(x, y);
	x = CLOCK_FIRST_DIGIT_X + 4 * CLOCK_DIGIT_WIDTH + CLOCK_DOTS_WIDTH;
	draw_clock_dots(x, y);
}

/* Rutina de interrupci�n del timer. Se activa una vez por segundo
 */
void interval_timer_isr()
{

	*(interval_timer_ptr) = 0;  		// Elimina la interruci�n

	count++; 							// Incrementa la cuenta del timer.
	if (count >= 86400) {count = 0;}  	// Reset si es igual o mayor a 24 horas

	seconds_to_time_t(count, &time);  	// Actualiza la estructura
	send_time_to_7seg(&time);  			// Env�a el reloj por los displays de 7 segmentos
	send_time_to_lcd_1602(&time);		// Env�a el reloj por el LCD
	draw_clock(&time);

	return;
}


/* Rutina de interrupci�n de los pulsadores.
 */
void pushbutton_isr( )
{
	int press;

	press = *(KEY_ptr + 3);  			// Lee el registro de los pulsadores
	*(KEY_ptr + 3) = 0;      			// Elimina la interrupci�n

	if (press & 0x4) {  // Se ha pulsado el KEY2 (0100)
		count += 60;
		if (count >= 86400) {count = count % 60;}  // si >24 horas, no perder segundos
    }
	if (press & 0x8) {  // Se ha pulsado el KEY3 (1000)
    	count += 3600;
		if (count >= 86400) {count = count % 3600;}  // si >24 horas no perder mins y segs
 	}

	seconds_to_time_t(count, &time);  	// Actualiza la estructura
	send_time_to_7seg(&time);  			// Env�a el reloj por los displays de 7 segmentos
	send_time_to_lcd_1602(&time);		// Env�a el reloj por el LCD
	draw_clock(&time);

	return;
}


int color_8_to_16_bits(int color_8bits) {

	int r = 0;

	for (int i = 0; i < 8; i++) {
		r |= ((color_8bits & (1 << i)) << i) | ((color_8bits & (1 << i)) << (i + 1));
	}
	return r;
}



/* Rutina de interrupci�n del slider. Se activa una vez por segundo
 */
void slider_switches_isr()
{
	int slider;

	slider = *(slider_switch_ptr + 3);  			// Lee el registro de los pulsadores
	*(slider_switch_ptr + 3) = 0;      			// Elimina la interrupci�n

	background_color_8b = (slider >> 8) ^ background_color_8b;
	background_color = color_8_to_16_bits(background_color_8b);

	digit_color_8b = (slider & 0xFF) ^ digit_color_8b;
	digit_color = color_8_to_16_bits(digit_color_8b);

    MTL_fill_screen(background_color);
	draw_clock(&time);

	return;
}


/* Funci�n principal
 */
int main(void)
{
	int counter_init = 50000000;  // Valor del contador. 1/(50 MHz)�(50 M)= 1 s

	char text_bottom_row[40] = "J. Del Pino Mena";

	char MTL_text_title[40] = "State-of-the-art clock\0";
	char MTL_text_name[40] = "Juan Del Pino Mena\0";

	//int delay_MTL = 0;
	//alt_up_pixel_buffer_dma_dev *pixel_buffer_dev_MTL;

	alt_up_char_buffer_dev *char_buffer_dev_MTL;


	/* WELCOME */

	alt_printf("TAREA 1 - RELOJ\n");
	alt_printf("CHS - 2022\n");
	alt_printf("Juan Del Pino Mena\n");


	/* INICIALIZACION DE LA CUENTA */

	LCD_cursor(0,1);			// set LCD cursor location to bottom row
	LCD_text(text_bottom_row);
	LCD_cursor_off();			// turn off the LCD cursor

	// Inicializa los atributos de la estructura a nulos
	seconds_to_time_t(0, &time);

	// borra el contenido del LCD y del siete segmentos
	send_time_to_7seg(&time);
	send_time_to_lcd_1602(&time);


	/* CONFIGURACI�N DE INTERRUPCIONES */

	*(interval_timer_ptr + 0x2) = (counter_init & 0xFFFF); 			// copia parte baja
	*(interval_timer_ptr + 0x3) = (counter_init >> 16) & 0xFFFF;  	// copia parte alta

	// Comienzo del timer y las interrupciones.
	*(interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1
	alt_irq_register(TIMER_IRQ, NULL, interval_timer_isr);  // Habilita int. timer

	// Pulsadores
	*(KEY_ptr + 2) = 0xE;  	// M�scara de los pulsadores (keys 3210: 1110) (el 0 es reset)
	*(KEY_ptr + 3) = 0;		// Registro de los pulsadores a cero
	alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_isr);  // Habilitar int. pulsadores

	// Sliders
	*(slider_switch_ptr + 2) = 0xFFFF; // M�scara de los pulsadores (keys 3210: 1110) (el 0 es reset)
	*(slider_switch_ptr + 3) = 0;		 // Registro de los sliders a cero
	alt_irq_register(SWITCHES_IRQ, NULL, slider_switches_isr);  // Habilitar int. pulsadores


	/* INICIALIZACI�N DE LA PANTALLA MTL */

	/* BUFFER DE CARACTERES */

	// output text message in the middle of the MTL monitor
	char_buffer_dev_MTL = alt_up_char_buffer_open_dev("/dev/mtl_char_buffer");
	if (char_buffer_dev_MTL == NULL) {
		alt_printf("Error: could not open MTL character buffer device\n");
		return -1;  // error
	} else {
		alt_printf("Opened MTL character buffer device\n");
	}

	// Borra el buffer de caracteres de texto
	alt_up_char_buffer_clear(char_buffer_dev_MTL);

	// Dibujar el nombre del alumno en la pantalla.
	// S�lo es necesario llamarlo una vez porque se guarda en foreground.
    alt_up_char_buffer_string(char_buffer_dev_MTL, MTL_text_title, 14, 4);
    alt_up_char_buffer_string(char_buffer_dev_MTL, MTL_text_name, 16, 25);

    MTL_fill_screen(background_color);

	/* BUFFER DE PIXELES */  // NO UTILIZADO

	/*
	// initialize the MTL pixel buffer HAL
	pixel_buffer_dev_MTL = alt_up_pixel_buffer_open_dev ("/dev/mtl_pixel_buffer_dma");
	if (pixel_buffer_dev_MTL == NULL) {
		alt_printf ("Error: could not open MTL pixel buffer device\n");
		return -1;  // error
	} else {
		alt_printf ("Opened MTL pixel buffer device\n");
	}
	alt_printf("open\n");

	// Borra el contenido de la pantalla
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev_MTL, 0);
	alt_printf("clear\n");

	// Swap_buffer
	// alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev_MTL);

	alt_printf("swap\n");

	// espera a que el buffer se libre
	// while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer_dev_MTL));*/


	alt_printf("Main finish\n");


	/* SUPER-LOOP 
	 * Bucle principal infinito del programa, encargado de la salida por pantalla
	 */
	while(1)
	{
		//draw_clock(&time);
		/*
		// Espera a que la pantalla est� lista; una vez ha dibujado el frame anterior.
		if (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer_dev_MTL) == 0)
		{
			// Delay para reducir la velocidad de actualizaci�n de la pantalla a la mitad.
			delay_MTL = 1 - delay_MTL;

			if (delay_MTL == 0) 
			{
				draw_clock(&time, pixel_buffer_dev_MTL);
			}
			
			// Swap buffer, para checkear si la pantalla se ha dibujado. 
			alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev_MTL);
		}*/
	}
}




