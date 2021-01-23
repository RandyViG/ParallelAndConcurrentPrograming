#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

unsigned char * reservar_memoria( uint32_t width, uint32_t height ){
	unsigned char *imagen;
	imagen = (unsigned char *) malloc( width * height * sizeof( unsigned char    ) );
	if( imagen == NULL ){
		perror( "Error al asignar memoria a la imagen");
		exit( EXIT_FAILURE );
	}

	return imagen;
}

