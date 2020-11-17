#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"defs.h"

int * reservar_memoria( void ){
	int *mem;
	mem = (int*) malloc( N * sizeof(int) );
	if( !mem ){
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenar_arreglo( int *datos ){
	register int i;
	for( i = 0; i < N ; i++ )
		datos[i] = rand() % 256;
}

void imprimir_arreglo( int *datos){
	register int i;
	for( i = 0 ; i < N ; i++ ){
		if( !(i%16) && (i!=0) )
			printf("\n");
		printf("%3d ", datos[i]);
	}
	printf("\n");	
}

