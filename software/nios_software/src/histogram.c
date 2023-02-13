#include "../inc/task_config.h"
#include "../inc/sdcard.h"
#include <math.h>

void MTL_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;
	//Escribir directamente en la pantalla SD (antes del escalado y etc) 0x09100000
	int SRAM_BASE_SIN_CACHE = (0x09100000 + 0x080000000);  //Activando el bit m�s significativo se elude la cache de datos
  	volatile short * pixel_buffer = (short *) SRAM_BASE_SIN_CACHE;	// MTL pixel buffer

  	// se asume que las coordenadas del rectangulo son correctas
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
void MTL_box2(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;
	int SRAM_BASE_SIN_CACHE = (0x09100000 + 0x080000000);  //Activando el bit m�s significativo se elude la cache de datos
  	volatile short * pixel_buffer = (short *) SRAM_BASE_SIN_CACHE;	// MTL pixel buffer

  	// se asume que las coordenadas del rectangulo son correctas
	for (row = y1; row <= y2; row++)
	{
		col = x1;
		while (col <= x2)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) |= pixel_color;	//procesa mitad direcciones
			++col;
		}
	}
}

volatile int R[200] = {23, 10, 10, 14, 26, 31, 21, 5, 21, 24, 19, 19, 22, 3, 10, 23, 27, 31, 13, 19, 30, 11, 3, 12, 10, 22, 31, 10, 30, 6, 13, 31, 25, 22, 30, 1, 30, 5, 27, 0, 17, 10, 14, 26, 20, 28, 15, 0, 5, 19, 10, 1, 16, 3, 26, 5, 31, 28, 23, 29, 14, 19, 9, 31, 17, 15, 0, 24, 26, 24, 16, 28, 14, 12, 19, 4, 10, 3, 19, 9, 14, 6, 11, 22, 4, 15, 10, 19, 9, 13, 18, 31, 17, 30, 19, 13, 27, 19, 2, 27, 20, 8, 30, 2, 17, 2, 10, 8, 29, 30, 14, 24, 19, 16, 2, 24, 27, 10, 0, 4, 6, 14, 30, 8, 3, 8, 27, 19, 14, 18, 20, 22, 5, 30, 21, 20, 9, 29, 11, 12, 7, 22, 1, 29, 10, 30, 27, 24, 20, 15, 2, 25, 2, 18, 31, 22, 19, 18, 17, 19, 6, 21, 27, 6, 24, 31, 29, 12, 29, 26, 25, 2, 24, 7, 16, 0, 21, 16, 14, 5, 7, 11, 16, 12, 8, 15, 0, 1, 18, 20, 12, 5, 14, 10, 25, 8, 20, 24, 26, 5};
volatile int G[200] = {4, 29, 15, 28, 13, 0, 17, 4, 25, 0, 28, 30, 26, 3, 21, 23, 12, 13, 25, 28, 4, 13, 4, 29, 9, 23, 17, 20, 20, 5, 4, 6, 22, 12, 17, 11, 13, 31, 18, 31, 28, 23, 1, 25, 24, 20, 7, 16, 9, 17, 31, 26, 10, 9, 20, 21, 9, 30, 13, 25, 7, 29, 5, 4, 17, 30, 10, 8, 17, 27, 28, 31, 7, 30, 9, 11, 18, 17, 17, 5, 10, 30, 8, 30, 23, 0, 28, 16, 21, 31, 28, 25, 22, 28, 13, 1, 3, 7, 22, 10, 6, 26, 6, 9, 26, 10, 1, 20, 1, 29, 2, 3, 6, 27, 8, 23, 0, 21, 6, 15, 9, 8, 15, 7, 2, 23, 3, 2, 19, 22, 27, 20, 16, 21, 8, 23, 22, 26, 16, 4, 2, 7, 11, 11, 8, 12, 2, 1, 23, 18, 22, 19, 6, 31, 27, 30, 28, 12, 10, 22, 3, 4, 19, 3, 17, 13, 17, 14, 27, 27, 4, 25, 4, 18, 25, 9, 16, 26, 22, 2, 24, 2, 11, 12, 17, 13, 10, 20, 15, 3, 5, 14, 5, 29, 17, 15, 1, 27, 17, 22};
volatile int B[200] = {17, 15, 27, 3, 8, 2, 4, 18, 22, 27, 3, 0, 2, 13, 14, 24, 13, 31, 12, 21, 29, 26, 17, 27, 22, 13, 16, 12, 19, 15, 0, 10, 13, 9, 2, 0, 28, 28, 2, 1, 3, 1, 8, 7, 10, 8, 17, 26, 20, 13, 9, 7, 23, 17, 9, 15, 30, 19, 22, 19, 3, 11, 25, 3, 4, 19, 28, 10, 23, 9, 29, 24, 13, 27, 24, 21, 8, 25, 31, 6, 27, 4, 10, 31, 26, 29, 26, 7, 28, 26, 12, 29, 4, 1, 20, 10, 26, 23, 25, 1, 6, 5, 28, 10, 23, 11, 29, 29, 2, 20, 0, 27, 0, 30, 23, 21, 9, 2, 10, 31, 11, 17, 2, 6, 5, 10, 15, 16, 22, 17, 28, 25, 24, 27, 12, 1, 7, 17, 12, 25, 5, 28, 15, 6, 12, 14, 25, 13, 29, 22, 10, 23, 30, 1, 21, 16, 13, 23, 18, 21, 7, 1, 25, 29, 27, 17, 3, 7, 22, 12, 25, 19, 2, 4, 13, 14, 13, 29, 3, 4, 11, 28, 16, 28, 0, 8, 1, 15, 12, 2, 2, 24, 29, 15, 23, 23, 29, 9, 27, 20};
volatile short color_R = 0xF000;
volatile short color_G = 0x0F00;
volatile short color_B = 0x00F0;

#define pi 3.142857

void actualizar_histograma(){

	//Histograma con funciones senoidales
	for (int i = 0; i <= 199; i++){
		MTL_box2 (4+1*i, 231-(sin(pi/4+(i*pi)/180))*110, 5+1*i, 235, color_R);
		MTL_box2 (4+1*i, 231-(sin(pi/6+(i*pi)/180))*110, 5+1*i, 235, color_G);
		MTL_box2 (4+1*i, 231-(sin(pi/10+((i*pi)/180)))*110, 5+1*i, 235, color_B);
	}

	//Histograma con barras

	/*for (int i = 0; i <= 199; i++){
		MTL_box2 (4+1*i, 231-(R[i]*120/32-4), 5+1*i, 235, color_R);
		MTL_box2 (4+1*i, 231-(G[i]*120/32-4), 5+1*i, 235, color_G);
		MTL_box2 (4+1*i, 231-(B[i]*120/32-4), 5+1*i, 235, color_B);
	}*/
}

void TaskHistogram(void *pdata){//Leer que hay ahora en pantalla, dibujar un histograma y reanudar
	INT8U err;
	while(1){
		OSMboxPend(drawHist, 0, &err);
		//Leer contenidos de la pantalla

		//Escribir en pantalla - Directamente
		actualizar_histograma();
		//Fin
		isSaving = false;//Deberia usar su propia variable
	}
}
