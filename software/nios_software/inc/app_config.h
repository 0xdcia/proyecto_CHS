/* Configuracion global de la aplicación */

/* Variables globales */
extern volatile int * red_LED_ptr;
extern volatile int * green_LED_ptr;
extern volatile int * HEX3_HEX0_ptr;
extern volatile int * HEX7_HEX4_ptr;
extern volatile int * KEY_ptr;
extern volatile int * SW_switch_ptr;
extern volatile char * LCD_display_ptr;
extern volatile short * pixel_buffer;
extern volatile char * character_buffer;

/* Antes de lanzar cualquier tarea */
void Init_App(void);
