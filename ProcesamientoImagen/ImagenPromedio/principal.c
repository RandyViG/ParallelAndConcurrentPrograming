#include<stdio.h>
#include<stdlib.h>
#include"imagen.h"

unsigned char * reservar_memoria( uint32_t width, uint32_t height );
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );

int main( void ){
	bmpInfoHeader info;
	unsigned char *imagenRGB, *imagenGray;
	
	imagenRGB = abrirBMP( "../Imagenes/hoja.bmp", &info );
	displayInfo( &info );
	imagenGray = reservar_memoria( info.width, info.height );
	RGBToGray( imagenRGB, imagenGray, info.width, info.height );
	GrayToRGB( imagenRGB, imagenGray, info.width, info.height );

	guardarBMP( "hojaNG.bmp", &info, imagenRGB );
	free( imagenRGB );
	free( imagenGray );
	return 0;
}

unsigned char * reservar_memoria( uint32_t width, uint32_t height ){
	unsigned char *imagen;
	imagen = (unsigned char *) malloc( width * height * sizeof( unsigned char ) );
	if( imagen == NULL ){
		perror( "Error al asignar memoria a la imagen");
		exit( EXIT_FAILURE );
	}

	return imagen;
}

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int x, y;
	int indiceGray, indiceRGB;
	unsigned char nivelGris;
	for( y = 0 ; y < height ; y++ )
		for( x = 0 ; x < width ; x++ ){
			indiceGray = y *  width + x;
			indiceRGB = indiceGray * 3 ;
			nivelGris = (imagenRGB[indiceRGB] + imagenRGB[indiceRGB+1] + imagenRGB[indiceRGB+2]) / 3;
			imagenGray[indiceGray] = nivelGris;
		}
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int x, y;
	int indiceGray, indiceRGB;
	for( y = 0 ; y < height ; y++ )
		for( x = 0 ; x < width ; x++ ){
			indiceGray = y *  width + x;
			indiceRGB = indiceGray * 3 ;
			imagenRGB[indiceRGB] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
		}
}

