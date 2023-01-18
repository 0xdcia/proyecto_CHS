/* Ejemplo de uso de los puertos paralelos, LCD y MTL en DE2
 * Este programa realiza lo siguiente:
 * 1. Visualiza el valor de los interruptores SW en los LED rojos LEDR
 * 2. Visualiza el valor de los pulsadores KEY[3..1] en los LED verdes LEDG
 * 3. Visualiza un patrón que va girando en los displays 7-segmentos HEX
 * 4. Al pulsar los KEY[3..1], el valor de los interruptores SW se toma como patrón
 * 5. Escribe un mensaje en el LCD
 * 6. Escribe un mensaje en el centro de la pantalla MTL
*/

#include "system.h"
#include <stdio.h>

/* funciones */
void LCD_cursor( int, int );
void LCD_text( char * );
void LCD_cursor_off( void );
void MTL_text (int, int, char *);
void MTL_box (int, int, int, int, short);

int main(void)
{
	/* Declarar los punteros a registros de I/O como volatile (volatile significa que
 	* que tanto las instrucciones de lectura como las de escritura se pueden utilizar
 	* para acceder a estas posiciones en lugar de realizar accesos a memoria
	*/
	volatile int * red_LED_ptr = (int *) RED_LEDS_BASE; 	// dirección LED rojos
	volatile int * green_LED_ptr = (int *) GREEN_LEDS_BASE; // dirección LED verdes
	volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE; 	// dirección HEX3_HEX0
	volatile int * HEX7_HEX4_ptr = (int *) HEX7_HEX4_BASE; 	// dirección HEX7_HEX4
	volatile int * SW_switch_ptr = (int *) SWITCHES_BASE; 	// dirección SW
	volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE; 		// dirección pulsadores KEY

	int HEX_bits = 0x0000000F; 								// patrón para los display HEX
	int SW_value, KEY_value, delay_count;

	printf("Hola desde Nios II\n");

	/* mensaje a visualizar en la VGA y en el LCD */
	char text_top_row[40] = "Altera DE2-115\0";
	char text_bottom_row[40] = "Media Computer\0";

	/* escribe el texto en el LCD */
	LCD_cursor (0,0);						// fija el cursor del LCD en la fila superior
	LCD_text (text_top_row);
	LCD_cursor (0,1);						// fija el cursor del LCD en la fila inferior
	LCD_text (text_bottom_row);
	LCD_cursor_off ();						// apaga el cursor del LCD

	/* crea el texto en medio del monitor VGA */
	MTL_text (20, 14, text_top_row);
	MTL_text (20, 15, text_bottom_row);
	MTL_box (0, 0, 50*8-1, 30*8-1, 0x0000); // Pinta de Negro toda la pantalla
	MTL_box (19*8, 13*8, 35*8, 17*8, 0x187F); //Dibuja un cuadro azul en el centro

	while(1)
	{
		SW_value = *(SW_switch_ptr); 						// leer el valor de los interruptores SW
		*(red_LED_ptr) = SW_value; 							// encender los LED rojos
		KEY_value = *(KEY_ptr); 							// leer el valor de los pulsadores KEY
		*(green_LED_ptr) = KEY_value;						// encender los LED verdes
		if (KEY_value != 0)									// mirar si se ha pulsado algún KEY
		{
			HEX_bits = SW_value;							// establecer el patrón con el valor de SW
			while (*KEY_ptr);								// esperar a que se vuelva a pulsar algún KEY
		}
		*(HEX3_HEX0_ptr) = HEX_bits;						// visualizar patrón en HEX3 ... HEX0
		*(HEX7_HEX4_ptr) = HEX_bits;						// visualizar patrón en HEX7 ... HEX4

		/* girar el patrón mostrado en los displays HEX */
		if (HEX_bits & 0x80000000)
			HEX_bits = (HEX_bits << 1) | 1;
		else
			HEX_bits = HEX_bits << 1;

		for (delay_count = 200000; delay_count != 0; --delay_count); 	//retardo
	}
}

/****************************************************************************************
 * Subrutina para mover el cursor del LCD
****************************************************************************************/
void LCD_cursor(int x, int y)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display
	char instruction;

	instruction = x;
	if (y != 0) instruction |= 0x40;			// activar el bit 6 para la fila inferior
	instruction |= 0x80;						// hay que activar el bit 7 para indicar el lugar
	*(LCD_display_ptr) = instruction;			// escribe registro de instrucciones del LCD
}

/****************************************************************************************
 * Subrutina para enviar una cadena de texto al LCD
****************************************************************************************/
void LCD_text(char * text_ptr)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display

	while ( *(text_ptr) )
	{
		*(LCD_display_ptr + 1) = *(text_ptr);	// escribe los datos en el LCD
		++text_ptr;
	}
}

/****************************************************************************************
 * Subrutina para apagar el cursor del LCD
****************************************************************************************/
void LCD_cursor_off(void)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display
	*(LCD_display_ptr) = 0x0C;										// desactiva el curso del LCD
}

/****************************************************************************************
 * Subrutina para enviar una cadena de texto a la pantalla MTL
****************************************************************************************/
void MTL_text(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *)  MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE;	// MTL character buffer

  	/* asume que la cadena de texto comienza en la primera fila */
	offset = (y << 6) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// escribe en el buffer
		++text_ptr;
		++offset;
	}
}

/****************************************************************************************
 * Dibujar un rectangulo en la pantalla MTL
****************************************************************************************/
void MTL_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;
	int SRAM_BASE_SIN_CACHE = (SRAM_BASE + 0x080000000);  //Activando el bit más significativo se elude la cache de datos
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
