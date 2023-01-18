/*
 * media_graphics_HAL.c
 *
 *  Created on: 19 de oct. de 2022
 *      Author: jdelpin
 */


#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "sys/alt_stdio.h"

void draw_big_A(alt_up_pixel_buffer_dma_dev *);
void LCD_cursor( int, int );
void LCD_text( char * );
void LCD_cursor_off( void );
void HEX_PS2(char);

/********************************************************************************
 * This program demonstrates use of the character and pixel buffer HAL code for
 * the DE2 Media computer. It:
 * 	-- places a blue box on the VGA display, and places a text string inside the box.
 *		-- draws a big A on the screen, for ALTERA
 *		-- "bounces" a colored box around the screen
********************************************************************************/
int main(void)
{
	alt_up_pixel_buffer_dma_dev *pixel_buffer_dev_MTL;
	alt_up_char_buffer_dev *char_buffer_dev_MTL;

	/* used for drawing coordinates */
	int x3, y3, x4, y4, deltax_3, deltax_4, deltay_3, deltay_4, delay_MTL = 0;

	/* create a message to be displayed on the VGA display */
	char text_top_row[40] = "Altera DE2-115\0";
	char text_bottom_row[40] = "Media Computer\0";
	char byte1 = 0;
	short nibbles = 0;
	int count = 0;

	/* output text message to the LCD */
	LCD_cursor (0,0);										// set LCD cursor location to top row
	LCD_text (text_top_row);
	LCD_cursor (0,1);										// set LCD cursor location to bottom row
	LCD_text (text_bottom_row);
	LCD_cursor_off ();									// turn off the LCD cursor

	byte1 = (nibbles << 4 | nibbles) ;
	HEX_PS2 (byte1);


	/* initialize the MTL pixel buffer HAL */
	pixel_buffer_dev_MTL = alt_up_pixel_buffer_dma_open_dev ("/dev/mtl_pixel_buffer_dma");
	if ( pixel_buffer_dev_MTL == NULL)
		alt_printf ("Error: could not open MTL pixel buffer device\n");
	else
		alt_printf ("Opened MTL pixel buffer device\n");
	/* clear the graphics screen */
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev_MTL, 0);

	/* output text message in the middle of the MTL monitor */
	char_buffer_dev_MTL = alt_up_char_buffer_open_dev ("/dev/mtl_char_buffer");
	if (char_buffer_dev_MTL == NULL)
	{
		alt_printf ("Error: could not open MTL character buffer device\n");
		return -1;
	}
	else
		alt_printf ("Opened MTL character buffer device\n");
	alt_up_char_buffer_string (char_buffer_dev_MTL, text_top_row, 20, 14);
	alt_up_char_buffer_string (char_buffer_dev_MTL, text_bottom_row, 20, 15);


	/* now draw a background box for the text */
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev_MTL, 19*8, 13*8, 35*8, 17*8,  0x187F, 0);

	/* now draw a big A for ALTERA */
	draw_big_A (pixel_buffer_dev_MTL);

	/* now draw a red rectangle with diagonal green lines */
	x3 = 20; y3 = 20;
	x4 = 50; y4 = 50;
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0xF800, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0x07e0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y4, x4, y3, 0x07e0, 0);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev_MTL);

	/* set the direction in which the box will move */
	deltax_3 = deltax_4 = deltay_3 = deltay_4 = 1;

	while(1)
	{

		if (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer_dev_MTL) == 0)
		{
			/* If the screen has been drawn completely then we can draw a new image. This
			 * section of the code will only be entered once every 60th of a second, because
			 * this is how long it take the VGA controller to copy the image from memory to
			 * the screen. */
			delay_MTL = 1 - delay_MTL;

			if (delay_MTL == 0)
			{
				/* The delay is inserted to slow down the animation from 60 frames per second
				 * to 30. Every other refresh cycle the code below will execute. We first erase
				 * the box with Erase Rectangle */

				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0, 0);
				alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0, 0);
				alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y4, x4, y3, 0, 0);

				// move the rectangle
				x3 = x3 + deltax_3;
				x4 = x4 + deltax_4;
				y3 = y3 + deltay_3;
				y4 = y4 + deltay_4;
				if ((deltax_3 > 0) && (x3 >= alt_up_pixel_buffer_dma_x_res(pixel_buffer_dev_MTL) - 1))
				{
					x3 = alt_up_pixel_buffer_dma_x_res(pixel_buffer_dev_MTL) - 1;
					deltax_3 = -deltax_3;
				}
				else if ((deltax_3 < 0) && (x3 <= 0))
				{
					x3 = 0;
					deltax_3 = -deltax_3;
				}
				if ((deltax_4 > 0) && (x4 >= alt_up_pixel_buffer_dma_x_res(pixel_buffer_dev_MTL) - 1))
				{
					x4 = alt_up_pixel_buffer_dma_x_res(pixel_buffer_dev_MTL) - 1;
					deltax_4 = -deltax_4;
				}
				else if ((deltax_4 < 0) && (x4 <= 0))
				{
					x4 = 0;
					deltax_4 = -deltax_4;
				}
				if ((deltay_3 > 0) && (y3 >= alt_up_pixel_buffer_dma_y_res(pixel_buffer_dev_MTL) - 1))
				{
					y3 = alt_up_pixel_buffer_dma_y_res(pixel_buffer_dev_MTL) - 1;
					deltay_3 = -deltay_3;
				}
				else if ((deltay_3 < 0) && (y3 <= 0))
				{
					y3 = 0;
					deltay_3 = -deltay_3;
				}
				if ((deltay_4 > 0) && (y4 >= alt_up_pixel_buffer_dma_y_res(pixel_buffer_dev_MTL) - 1))
				{
					y4 = alt_up_pixel_buffer_dma_y_res(pixel_buffer_dev_MTL) - 1;
					deltay_4 = -deltay_4;
				}
				else if ((deltay_4 < 0) && (y4 <= 0))
				{
					y4 = 0;
					deltay_4 = -deltay_4;
				}

				// redraw Rectangle with diagonal lines
				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0xF800, 0);
				alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y3, x4, y4, 0x07e0, 0);
				alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev_MTL, x3, y4, x4, y3, 0x07e0, 0);

				// redraw the box in the foreground
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev_MTL, 19*8, 13*8, 35*8, 17*8, 0x187F, 0);

				draw_big_A (pixel_buffer_dev_MTL);
			}

			/* Execute a swap buffer command. This will allow us to check if the screen has
			 * been redrawn before generating a new animation frame. */
			alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev_MTL);
		}

		if (count == 600000)
		{
			count = 0;
			if (nibbles == 15)
				nibbles = 0;
			else
				nibbles++;

			byte1 = nibbles;
			HEX_PS2 (byte1);
		}
		else
			count++;

	}
}

/* draws a big letter A on the screen */
void draw_big_A(alt_up_pixel_buffer_dma_dev *pixel_buffer_dev )
{
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 10, 88, 44, 10, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 44, 10, 72, 10, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 72, 10, 106, 88, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 106, 88, 81, 88, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 81, 88, 75, 77, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 75, 77, 41, 77, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 41, 77, 35, 88, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 35, 88, 10, 88, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 47, 60, 58, 32, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 58, 32, 69, 60, 0xffff, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer_dev, 69, 60, 47, 60, 0xffff, 0);
}

/****************************************************************************************
 * Subroutine to move the LCD cursor
****************************************************************************************/
void LCD_cursor(int x, int y)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display
	char instruction;

	instruction = x;
	if (y != 0) instruction |= 0x40;				// set bit 6 for bottom row
	instruction |= 0x80;								// need to set bit 7 to set the cursor location
	*(LCD_display_ptr) = instruction;			// write to the LCD instruction register
}

/****************************************************************************************
 * Subroutine to send a string of text to the LCD
****************************************************************************************/
void LCD_text(char * text_ptr)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display

	while ( *(text_ptr) )
	{
		*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		++text_ptr;
	}
}

/****************************************************************************************
 * Subroutine to turn off the LCD cursor
****************************************************************************************/
void LCD_cursor_off(void)
{
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;	// 16x2 character display
	*(LCD_display_ptr) = 0x0C;											// turn off the LCD cursor
}

/****************************************************************************************
 * Subroutine to show a string of HEX data on the HEX displays
****************************************************************************************/
void HEX_PS2(char b1)
{
	volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE;
	volatile int * HEX7_HEX4_ptr = (int *) HEX7_HEX4_BASE;
	volatile int * RED_LEDS_ptr = (int *) RED_LEDS_BASE;
	volatile int * GREEN_LEDS_ptr = (int *) GREEN_LEDS_BASE;

	/* SEVEN_SEGMENT_DECODE_TABLE gives the on/off settings for all segments in
	 * a single 7-seg display in the DE2 Media Computer, for the hex digits 0 - F */
	unsigned char	seven_seg_decode_table[] = {	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
		  										0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
	unsigned char	hex_segs[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned int leds;
	unsigned int nibble;
	unsigned char code;
	int i;

	nibble = b1 & 0x0F;
	code = seven_seg_decode_table[nibble];
	for ( i = 0; i < 8; ++i )
	{
		hex_segs[i] = code;
	}

	leds = (nibble << 16 | nibble << 12 | nibble << 8 | nibble << 4 | nibble);

	/* drive the hex displays */
	*(HEX3_HEX0_ptr) = *(int *) (hex_segs);
	*(HEX7_HEX4_ptr) = *(int *) (hex_segs+4);

	*(RED_LEDS_ptr) = leds;
	*(GREEN_LEDS_ptr) = leds;
}

