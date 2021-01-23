#include<stdio.h>
#include<pthread.h>
#include"defs.h"
#include"procesamiento.h"

extern float *pulso, *hann, *producto, *resultado;

void * fun_hilo( void *arg ){
	int nucleo = *(int*)arg;
	register int i;
	
	for( i = nucleo ; i < N ; i += NUM_HILOS )
		producto[i] = pulso[i] * hann[i];

	pthread_exit( arg );
}

void * autocorrelacion( void *arg ){
	int nucleo = *(int*)arg;
	int suma;
	register int l, n;
	for( l = nucleo ; l < N ; l += NUM_HILOS ){
		suma = 0;
		for( n = l ; n < N ; n++ )
			suma += producto[n] * producto[n-l];
		resultado[l] = suma;
	}
	pthread_exit( arg );
}
