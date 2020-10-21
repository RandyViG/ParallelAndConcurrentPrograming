#include<stdio.h>
#include"defs.h"

void ordenamiento( int *datos ){
	int aux;
	register int i,j;
	for( i = 0 ; i < N ; i++ )
		for( j = 0 ; j < N-1 ; j++ )
			if( datos[j] > datos[j+1] ){
				aux = datos[j+1];
				datos[j+1] = datos[j];
				datos[j] = aux;
			}
}

int promedio( int *datos ){
	int prom = 0;
	register int i;
	for( i = 0 ; i < N ; i++ )
		prom += datos[i];
	prom = prom / N;

	return prom;
}

int numerosPares( int *datos ){
	int cont = 0;
	register int i;
	for( i = 0 ; i < N ; i++ )
	       if( datos[i]%2 == 0 )
			cont++;
	
	return cont;	
}

void multiplicarDatos( int *datos ){
	register int i;
	for( i = 0; i < N ; i++ )
		datos[i] = datos[i] * C;	
}
