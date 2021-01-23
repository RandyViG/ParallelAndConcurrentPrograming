#include<stdio.h>
#include<pthread.h>
#include"defs.h"

extern int *A, *B, producto_punto;
extern pthread_mutex_t bloqueo;

void * fun_hilo( void *arg ){
	register int i;
	int nucleo, inicio, fin, elem_bloque, suma = 0;

	nucleo = *(int*)arg;
	elem_bloque = N / NUM_HILOS;
	inicio = nucleo * elem_bloque;
	fin = inicio + elem_bloque;
	
	for( i = inicio ; i < fin ; i++ )
		suma += ( A[i] * B[i] );

	pthread_mutex_lock( &bloqueo );
	producto_punto += suma;
	pthread_mutex_unlock( &bloqueo );

	pthread_exit( arg );
}

