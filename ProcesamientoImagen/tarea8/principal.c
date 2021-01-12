#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"defs.h"
#include"helper.h"
#include"hilos.h"
#include"imagen.h"
#include"procesamiento.h"

#define PATH "../Imagenes/"

unsigned char *imagenRGB, *imagenGray, *imagenS;

int main( int argc, char *argv[] ){
	if( argc < 2 ){
		printf("Falta el nombre de la imagen: ./%s huella1\n", argv[0]);
		exit( EXIT_FAILURE );
	}
	
	register int nh;
	int *hilo;
	char imagen[100], imagenFinal[100];
	struct params parametros[ NUM_HILOS ];
	pthread_t tids[ NUM_HILOS ];
	bmpInfoHeader info;
	memset( imagen, 0, 100 );
	sprintf(imagen, "%s%s", PATH, argv[1]);
	sprintf( imagenFinal, "Sobel_%s", argv[1]);

	imagenRGB = abrirBMP( imagen, &info );
	displayInfo( &info );
	imagenGray = reservar_memoria( info.width, info.height );
	imagenS = reservar_memoria( info.width, info.height );

	RGBToGray( imagenRGB, imagenGray, info.width, info.height );
	memset( imagenS, 255, info.width * info.height );
	
	for( nh = 0; nh < NUM_HILOS ; nh++ ){
		parametros[nh].width = info.width;
		parametros[nh].height = info.height;
		parametros[nh].nh = nh;
		pthread_create( &tids[nh], NULL, sobel, (void*)&parametros[nh] );
	}

	for( nh = 0; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh], (void**)&hilo );
		printf("El hilo %d termino..\n", *hilo );
	}
	//brilloImagen( imagenGray, info.width, info.height );
	GrayToRGB( imagenRGB, imagenS, info.width, info.height );
	
	guardarBMP( imagenFinal, &info, imagenRGB );

	free( imagenRGB );
	free( imagenGray );
	free( imagenS );

	return 0;
}
