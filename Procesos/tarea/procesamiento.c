#include<stdio.h>
#include"defs.h"

int buscarMayor( int *datos ){
	int mayor = datos[0];
	register int i;
	for( i = 1 ; i < N ; i++ )
		if( datos[i] > mayor )
			mayor = datos[i];

	return mayor;
}

int buscarMenor( int *datos ){
	int menor = datos[0];
	register int i;
	for( i = 1 ; i < N ; i++ )
		if( datos[i] < menor )
			menor = datos[i];

	return menor;
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
