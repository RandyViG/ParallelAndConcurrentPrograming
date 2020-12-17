#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"imagen.h"

#define DIMASK 3

unsigned char * reservar_memoria( uint32_t width, uint32_t height );
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height );
void filtroPB( unsigned char *imagenGray, unsigned char *imagenFiltrada, uint32_t width, uint32_t height );

int main( void ){
	bmpInfoHeader info;
	unsigned char *imagenRGB, *imagenGray, *imagenFiltrada;;
	
	imagenRGB = abrirBMP( "../Imagenes/huella1.bmp", &info );
	displayInfo( &info );
	
	imagenGray = reservar_memoria( info.width, info.height );
	imagenFiltrada = reservar_memoria( info.width, info.height );

	RGBToGray( imagenRGB, imagenGray, info.width, info.height );
	memset( imagenFiltrada, 255, info.width * info.height );
	filtroPB( imagenGray, imagenFiltrada, info.width, info.height );
	//brilloImagen( imagenGray, info.width, info.height );
	GrayToRGB( imagenRGB, imagenGray, info.width, info.height );
	
	guardarBMP( "huella1_FPB1.bmp", &info, imagenRGB );

	free( imagenRGB );
	free( imagenGray );

	return 0;
}

void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int indiceGray;
	int pixel;

	for( indiceGray = 0 ; indiceGray < (height * width) ; indiceGray++ ){
		pixel = imagenGray[indiceGray] + 70;
		imagenGray[indiceGray] = (pixel > 255) ? 255 : (unsigned char) pixel;
	}
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
	register int indiceGray, indiceRGB;
	unsigned char nivelGris;
	for( indiceGray = 0, indiceRGB = 0 ; indiceGray < ( height * width ) ; indiceGray++, indiceRGB += 3 ){
		nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2])/100;
		imagenGray[indiceGray] = nivelGris;
	}
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int indiceGray, indiceRGB;
	for( indiceGray = 0, indiceRGB = 0 ; indiceGray < ( height * width ) ; indiceGray++, indiceRGB += 3 ){
		imagenRGB[indiceRGB] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
	}
}

void filtroPB( unsigned char *imagenGray, unsigned char *imagenFiltrada, uint32_t width, uint32_t height ){
	register int x, y, ym, xm;
	int indicei, indicem, conv;
	int mascara[DIMASK*DIMASK] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	for( y = 0 ; y <= ( width - DIMASK ) ; y++ )
		for( x = 0 ; x <= ( width - DIMASK ) ; x++ ){
			indicem = 0;
			conv = 0;
			for( ym = 0 ; ym < DIMASK ; ym++ )
				for( xm = 0; xm < DIMASK ; xm++ ){
					indicei = (y+ym) * width + (x+xm);
					conv += imagenGray[indicei] * mascara[indicem++];
				}
			conv /= 9;
			indicei = (y+1) * width + (x+1);
			imagenFiltrada[indicei] = conv;
		}
}

