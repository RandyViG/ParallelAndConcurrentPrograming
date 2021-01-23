#include<stdio.h>
#include<pthread.h>
#include"defs.h"
#include"procesamiento.h"

extern float *pulso, *hann, *resultado;

void * fun_hilo( void *arg ){
	int nucleo = *(int*)arg;
	register int i;
	
	for( i = nucleo ; i < N ; i += NUM_HILOS )
		resultado[i] = pulso[i] * hann[i];

	pthread_exit( arg );
}

