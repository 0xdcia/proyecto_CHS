#include <stdio.h>
#include <string.h>
#include <Altera_UP_SD_Card_Avalon_Interface.h>
#include "../inc/task_config.h"
#include "../inc/sdcard.h"
#include "../inc/alt_ucosii_simple_error_check.h"

unsigned int getWord(short int *handle){
	unsigned int aux = 0;
	aux = alt_up_sd_card_read(*handle);
	aux |= alt_up_sd_card_read(*handle) << 8;
	aux |= alt_up_sd_card_read(*handle) << 16;
	aux |= alt_up_sd_card_read(*handle) << 24;
	return aux;
}

unsigned short getShort(short int *handle){
	unsigned short aux = 0;
	aux = (alt_up_sd_card_read(*handle));
	aux = aux | (alt_up_sd_card_read(*handle) << 8);
	return aux;
}

// Determina si se trata de un fichero BMP
bool isBMP(char archivo[13]){
	//Comprobar el nombre de fichero
	if(!strstr(archivo, ".bmp") && !strstr(archivo, ".BMP")){
		return false;
	}
	short int handle = -1;
	handle = alt_up_sd_card_fopen(archivo, false);
	if(handle == -1){
		printf("No se ha podido abrir %s", archivo);
		return false;
	}
	//Comprobar la cabecera y formato
	struct bmpFileHeader header;
	if(!getFileheader(&handle, &header)){
		printf("No se ha podido obtener la cabecera\n");
		return false;
	}

	//Comprobar si es un BMP
	if(header.signature != 0x4d42){
		printf("Header invalido: %s\n", archivo);
		return false;
	}
	alt_up_sd_card_fclose(handle);
	return true;
}

#define HEADER 14
bool getFileheader(short int *handle, struct bmpFileHeader* header_st){
	header_st->signature = getShort(handle);
	header_st->fileSize = getWord(handle);
	getWord(handle);
	header_st->offsetBMPdata = getWord(handle);
	return true;
}

bool getInfoheader(short int *handle, struct bmpInfoHeader* info_st){
	info_st->headerSize = getWord(handle);
	info_st->width = getWord(handle);
	info_st->heigth = getWord(handle);
	info_st->planes = getShort(handle);
	info_st->bits_per_pixel = getShort(handle);
	info_st->compression = getWord(handle);
	info_st->imageSize = getWord(handle);
	info_st->XpixelsM = getWord(handle);
	info_st->YpixelsM = getWord(handle);
	info_st->colorsUsed = getWord(handle);
	info_st->importantColors = getWord(handle);
	return true;
}

void TaskSdcard(void *pdata){
	printf("SdCard: Voy a dormir\n");
	void *p_msg;
	while(1){
		p_msg = OSMboxPend(getimg, 0, err);

		//alt_ucosii_check_return_code(err);
		OSTimeDlyHMSM(0, 0, 2, 0);
		printf("SdCard: Me despierto %d\n", p_msg);
	}

}
