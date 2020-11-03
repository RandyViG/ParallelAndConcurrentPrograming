#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"defs.h"

int * reservarMemoria( void ){
	int *mem;
	mem = (int*) malloc( N * sizeof(int) );
	if( !mem ){
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo( int *datos ){
	register int i;
	for( i = 0; i < N ; i++ )
		datos[i] = rand() % 256;
}

void imprimirArreglo( int *datos){
	register int i;
	for( i = 0 ; i < N ; i++ ){
		if( !(i%16) && (i!=0) )
			printf("\n");
		printf("%4d ", datos[i]);
	}
	printf("\n");	
}

