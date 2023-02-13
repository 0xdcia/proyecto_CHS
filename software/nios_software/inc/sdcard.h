#include <stdbool.h>
#define CONVERT_888RGB_TO_565BGR(r, g, b) (((b&0xFF) >> 3) | (((g&0xFF) >> 2) << 5) | (((r&0xFF) >> 3) << 11))

extern int image;
extern int num_imgs;
extern bool isSaving;

struct bmpFileHeader{
	unsigned short signature; /* Identificador mágico 'BM' */
	unsigned int fileSize; /* Tamaño del fichero en bytes */
	char reserved[4];
	unsigned int offsetBMPdata; /* Offset a los datos de imagen en bytes */
};//Header - 14 bytes


struct bmpInfoHeader{
	unsigned int headerSize; /* Tamaño del header en bytes */
	int width; /* Width y height */
	int heigth;
	unsigned short planes; /* Planos de color */
	unsigned short bits_per_pixel;//16 - 16bit rgb o 24 - 24 bit rgb
	unsigned int compression; /* Tipo de compresión */
	unsigned int imageSize;//Puede ser 0 si no viene comprimida
	int XpixelsM; /* Pixeles por metro*/
	int YpixelsM;
	unsigned int colorsUsed; /* Numero de colores */
	unsigned int importantColors;//0 -> todos
};//InfoHeader - 40 bytes

typedef struct{
	char red;
	char green;
	char blue;
	char reserved_b;
} rgbTable;

unsigned int getWord(short int *handle);

unsigned short getShort(short int *handle);

// Determina si se trata de un fichero BMP
bool isBMP(char archivo[13]);

#define HEADER 14
bool getFileheader(short int *handle, struct bmpFileHeader* header_st);

bool getInfoheader(short int *handle, struct bmpInfoHeader* info_st);

void TaskSdcard(void *pdata);

void TaskSaveImg(void *pdata);

void printHeader(struct bmpFileHeader* header);

void printInfo(struct bmpInfoHeader* info);
