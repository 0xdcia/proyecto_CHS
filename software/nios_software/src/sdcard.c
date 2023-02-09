#include <stdio.h>
#include <string.h>
#include <Ricardo_SD_Card_Avalon_Interface.h>
#include "../inc/task_config.h"
#include "../inc/sdcard.h"
#include "../inc/app_config.h"
#include "../inc/alt_ucosii_simple_error_check.h"
#include <io.h>

unsigned int getWord(short int *handle){
	unsigned int aux = 0;
	aux = alt_up_sd_card_read(*handle);
	aux |= alt_up_sd_card_read(*handle) << 8;
	aux |= alt_up_sd_card_read(*handle) << 16;
	aux |= alt_up_sd_card_read(*handle) << 24;
	return aux;
}

void writeWord(short int *handle, unsigned int value){
	alt_up_sd_card_write(*handle, value);
	alt_up_sd_card_write(*handle, value << 8);
	alt_up_sd_card_write(*handle, value << 16);
	alt_up_sd_card_write(*handle, value << 24);
}

void writeShort(short int *handle, unsigned short value){
	alt_up_sd_card_write(*handle, value);
	alt_up_sd_card_write(*handle, value << 8);
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

bool setFileheader(short int *handle, struct bmpFileHeader* header_st){
	writeShort(handle, header_st->signature);
	writeWord(handle, header_st->fileSize);
	writeWord(handle, 0);
	writeWord(handle, header_st->offsetBMPdata);
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

bool setInfoheader(short int *handle, struct bmpInfoHeader* info_st){
	writeWord(handle, info_st->headerSize);
	writeWord(handle, info_st->width);
	writeWord(handle, info_st->heigth);
	writeShort(handle, info_st->planes);
	writeShort(handle, info_st->bits_per_pixel);
	writeWord(handle, info_st->compression);
	writeWord(handle, info_st->imageSize);
	writeWord(handle, info_st->XpixelsM);
	writeWord(handle, info_st->YpixelsM);
	writeWord(handle, info_st->colorsUsed);
	writeWord(handle, info_st->importantColors);
	return true;
}

char archivos[512][13];
int num_imgs = 0;
int loadFiles(){
	alt_up_sd_card_dev* sd_card = alt_up_sd_card_open_dev(SD_CARD_NAME);
	if(sd_card == NULL){
		printf("No hemos podido abrir /dev/sdcard\n");
		return 0;
	}
	if(alt_up_sd_card_is_Present() ==  false){
		printf("No se ha detectado una tarjeta SD\n");
		return 0;
	}
	if(!alt_up_sd_card_is_FAT16()){
		printf("La tarjeta no est� en FAT16\n");
		return 0;
	}



	//find first
	char nombre[13];
	unsigned short i = 0;
	if(alt_up_sd_card_find_first(".", nombre) == 0){
		if(isBMP(nombre)){
			strcpy(archivos[i], nombre);
			//printf("Archivo bmp %s encontrado!\n", archivos[i]);
			i++;
		}
		//find next
		while(alt_up_sd_card_find_next(nombre)== 0){
			if(isBMP(nombre)){
				strcpy(archivos[i], &nombre[0]);
				//printf("Archivo bmp %s encontrado!\n", archivos[i]);
				i++;
			}

		}
		return i;
	}
	else{
		printf("Error encontrando archivos en el directorio '.'\n");
		return 0;
	}
}

//Lee todas las imagenes de la tarjeta sd
//Una vez despertada, dibuja en pantalla la imagen elegida
//Si la imagen cambia mientras se dibuja, se reinicia el dibujado

int image = 0;
struct bmpFileHeader header;
struct bmpInfoHeader info_st;
void TaskSdcard(void *pdata){
	/* Cambiar de donde lee la DMA de la pantalla */
	int SRAM_BASE_SIN_CACHE = (SRAM_BASE + 0x080000000);

	num_imgs=loadFiles();
	printf("SdCard: Voy a dormir, %d archivos\n", num_imgs);
	void *p_msg;
	INT8U err;
	volatile short * pixel_buffer = (short *) SRAM_BASE_SIN_CACHE;	// MTL pixel buffer

	while(1){
		p_msg = OSMboxPend(getimg, 0, &err);
		alt_ucosii_check_return_code(err);
		printf("SdCard: Me despierto %d\n", p_msg);
		int offset;

		short aux[3];
		int old_img = -1;
		short int handle = -1;

		while((image%num_imgs)!= old_img){
			old_img = (image%num_imgs);
			printf("SdCard: Dibujando imagen\n");
			handle = alt_up_sd_card_fopen(archivos[old_img], false);
			//getHeader
			getFileheader(&handle, &header);
			//getInfo
			getInfoheader(&handle, &info_st);
			//Pixeles
			for(int i = 240-1; i >= 0; i--){
				if((image%num_imgs)!= old_img){
					//Cerrar archivo y cargar el siguiente
					alt_up_sd_card_fclose(handle);
					printf("SdCard: Imagen cambiada\n");
					break;
				}
				for(int j = 0; j < 400; j++){
					offset = (i << 9) + j;
					aux[0] = alt_up_sd_card_read(handle);
					aux[1] = alt_up_sd_card_read(handle);
					aux[2] = alt_up_sd_card_read(handle);
					*(pixel_buffer + offset) = CONVERT_888RGB_TO_565BGR(aux[2], aux[1], aux[0]);

				}
			}
			alt_up_sd_card_fclose(handle);
		}
		printf("SdCard: Imagen dibujada %d\n", p_msg);
	}

}


void TaskSaveImg(void *pdata){
	void *p_msg;
	int img_handle = -1;

	while(1){
		int offset;
		p_msg = OSMboxPend(saveimg, 0, &err);
		//Leer imagen de 0x09100000 y guardar en sd
		char nombre[13];
		sprintf(nombre, "cap%d", num_imgs);
		img_handle = alt_up_sd_card_fopen(nombre, true);

		//Crear cabecera
		setFileheader(&img_handle, &header);
		setInfoheader(&img_handle, &info_st);

		//Pixeles
		int aux;
		for(int i = 240-1; i >= 0; i--){
			for(int j = 0; j < 400; j++){
				offset = (i << 9) + j;
				aux = (int*)(0x09100000 + offset);
				alt_up_sd_card_write(img_handle, aux);
				alt_up_sd_card_write(img_handle, aux>>8);
				alt_up_sd_card_write(img_handle, aux>>16);
			}
		}

		alt_up_sd_card_fclose(img_handle);
		//Reiniciar la toma de video
		*(EFFECT_ptr + 0) = 0x00000000;
		//Actualizar imagenes
		loadFiles();
	}

}
