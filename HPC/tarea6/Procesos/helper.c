#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"defs.h"

float * reservar_memoria( void ){
	float *mem;
	mem = (float*) malloc( N * sizeof(float) );
	if( !mem ){
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenar_arreglo( float *datos ){
	register int i;
	for( i = 0; i < N ; i++ )
		datos[i] = rand() % 256;
}

void imprimir_arreglo( float *datos){
	register int i;
	for( i = 0 ; i < N ; i++ ){
		if( !(i%16) && (i!=0) )
			printf("\n");
		printf("%f ", datos[i]);
	}
	printf("\n");	
}

