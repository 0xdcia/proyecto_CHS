#include "system.h"

/* globales */
#define BUF_SIZE 500000		// alrededor de 10 segundos (@ 48K muestras/seg)
#define BUF_THRESHOLD 96		// 75% de 128 palabras

/* funciones */
void LCD_cursor( int, int );
void LCD_text( char * );
void LCD_cursor_off( void );
void MTL_text (int, int, char *);
void MTL_box (int, int, int, int, short);
void HEX_PS2(char, char, char);
void check_KEYs( int *, int *, int * );

/********************************************************************************
 * Este programa demuestra el uso de las funciones HAL
 *
 * En el se realiza los siguiente:
 *  1. Graba 10 segundos de audio cuando se pulsa KEY[1]. LEDG[0] permanece
 *     encendido mientras se está grabando.
 *  2. Reproduce el audio grabado cuando se pulsa KEY[2]. LEDG[1] permanece
 *     encendido mientras se está grabando.
 *	3. Dibuja un cuadro azul en el centro de la MTL y escribe un texto en
 *	   su interior.
 *	4. Muestra un mensaje en el LCD.
 *	5. Muestra en el display HEX los tres últimos bytes de datos recibidos
 *	   por el puerto PS/2.
 ********************************************************************************/

int main(void)
{
  	volatile int * green_LED_ptr = (int *) GREEN_LEDS_BASE;		// dirección LED verde
	volatile int * audio_ptr = (int *) AUDIO_BASE;			// dirección puerto audio
	volatile int * PS2_ptr = (int *) PS2_KEY_BASE;			// dirección puerto PS/2

	/* utiliado para grabar reproducir audio */
	int fifospace;
	int record = 0, play = 0, buffer_index = 0;
	int left_buffer[BUF_SIZE];
	int right_buffer[BUF_SIZE];

	/* utilizado en el puerto PS/2 */
	int PS2_data, RVALID;
	char byte1 = 0, byte2 = 0, byte3 = 0;

	/* mensaje que se visualizará en el LCD y en la MTL */
	char text_top_row[40] = "Altera DE2-115\0";
	char text_bottom_row[40] = "Media Computer\0";

	/* Sacar mensaje en el LCD */
	LCD_cursor (0,0);								// poner el cursor del LCD en la fila superior
	LCD_text (text_top_row);
	LCD_cursor (0,1);								// poner el cursor del LCD en la fila inferior
	LCD_text (text_bottom_row);
	LCD_cursor_off ();								// desactivar el cursor del LCD

	/* crea el texto en medio del monitor MTL */
	MTL_text (20, 14, text_top_row);
	MTL_text (20, 15, text_bottom_row);
	MTL_box (0, 0, 50*8-1, 30*8-1, 0x0000); // Pinta de Negro toda la pantalla
	MTL_box (19*8, 13*8, 35*8, 17*8, 0x187F); //Dibuja un cuadro azul en el centro

	/* leer y reproducir audio */
	record = 0;
	play = 0;

	// PS/2 necesita ser reseteado
	*(PS2_ptr) = 0xFF;		// reset
	while(1)
	{
		check_KEYs ( &record, &play, &buffer_index );
		if (record)
		{
			*(green_LED_ptr) = 0x1;					// LEDG[0] on
			fifospace = *(audio_ptr + 1);	 		// leer el puerto de audio
			if ( (fifospace & 0x000000FF) > BUF_THRESHOLD ) 	// chequear RARC
			{
				// almacenar datos hasta que la FIFO este vacia o el buffer este lleno
				while ( (fifospace & 0x000000FF) && (buffer_index < BUF_SIZE) )
				{
					left_buffer[buffer_index] = *(audio_ptr + 2);
					right_buffer[buffer_index] = *(audio_ptr + 3);
					++buffer_index;

					if (buffer_index == BUF_SIZE)
					{
						// grabación terminada
						record = 0;
						*(green_LED_ptr) = 0x0;				// LEDG off
					}
					fifospace = *(audio_ptr + 1);	// leer el puerto de audio
				}
			}
		}
		else if (play)
		{
			*(green_LED_ptr) = 0x2;					// LEDG[1] on
			fifospace = *(audio_ptr + 1);	 		// leer el puerto de audio
			if ( (fifospace & 0x00FF0000) > BUF_THRESHOLD ) 	// chequear WSRC
			{
				// sacar datos de audio hasta que el buffer se vacie o la FIFO se llene
				while ( (fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE) )
				{
					*(audio_ptr + 2) = left_buffer[buffer_index];
					*(audio_ptr + 3) = right_buffer[buffer_index];
					++buffer_index;

					if (buffer_index == BUF_SIZE)
					{
						// reproducción terminada
						play = 0;
						*(green_LED_ptr) = 0x0;				// LEDG off
					}
					fifospace = *(audio_ptr + 1);	// leer el puerto de audio
				}
			}
		}
		/* chequear datos PS/2 -- mostrar en display HEX */
		PS2_data = *(PS2_ptr);			// leer el puerto de datos PS/2
		RVALID = PS2_data & 0x8000;	// obtener el campo RVALID
		if (RVALID)
		{
			/* desplazar el nuevo dato al display */
			byte1 = byte2;
			byte2 = byte3;
			byte3 = PS2_data & 0xFF;
			HEX_PS2 (byte1, byte2, byte3);

			if ( (byte2 == (char) 0xAA) && (byte3 == (char) 0x00) )
				// raton conectado; initializar envio de datos
				*(PS2_ptr) = 0xF4;
		}
	}
}

/****************************************************************************************
 * Subrutina para mover el cursor del LCD
****************************************************************************************/
void LCD_cursor(int x, int y)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// display LCD 16x2
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
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// display LCD 16x2

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
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// display LCD 16x2
	*(LCD_display_ptr) = 0x0C;					// desactiva el curso del LCD
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
  	volatile short * pixel_buffer = (short *) SRAM_BASE_SIN_CACHE;	// VGA pixel buffer

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

/****************************************************************************************
 * Subrutine to para mostrar una cadena de datos HEX en el display HEX
****************************************************************************************/
void HEX_PS2(char b1, char b2, char b3)
{
	volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE;
	volatile int * HEX7_HEX4_ptr = (int *) HEX7_HEX4_BASE;

	unsigned char	seven_seg_decode_table[] = {	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                                                        0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
	unsigned char	hex_segs[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned int shift_buffer, nibble;
	unsigned char code;
	int i;

	shift_buffer = (b1 << 16) | (b2 << 8) | b3;
	for ( i = 0; i < 6; ++i )
	{
		nibble = shift_buffer & 0x0000000F;
		code = seven_seg_decode_table[nibble];
		hex_segs[i] = code;
		shift_buffer = shift_buffer >> 4;
	}

	*(HEX3_HEX0_ptr) = *(int *) (hex_segs);
	*(HEX7_HEX4_ptr) = *(int *) (hex_segs+4);
}

/****************************************************************************************
 * Subrutina para leer KEYs
****************************************************************************************/
void check_KEYs(int * KEY1, int * KEY2, int * counter)
{
	volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE;
	volatile int * audio_ptr = (int *) AUDIO_BASE;
	int KEY_value;

	KEY_value = *(KEY_ptr);
	while (*KEY_ptr);

	if (KEY_value == 0x2)
	{
		// borrar contador para empezar a grabar
		*counter = 0;
		// borrar FIFO audio entrada
		*(audio_ptr) = 0x4;
		*(audio_ptr) = 0x0;

		*KEY1 = 1;
	}
	else if (KEY_value == 0x4)
	{
		// borrar contador para empezar a reproducir
		*counter = 0;
		// borrar FIFO audio salida
		*(audio_ptr) = 0x8;
		*(audio_ptr) = 0x0;

		*KEY2 = 1;
	}
}
