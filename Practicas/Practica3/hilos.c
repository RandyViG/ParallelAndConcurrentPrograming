#include<stdio.h>
#include<pthread.h>
#include"procesamiento.h"

extern pthread_mutex_t bloqueo;

void * funHilo( void *arg ){
	int nh = *(int*)arg;

	printf("Hilo %d en ejecucion \n",nh);
	pthread_mutex_lock( &bloqueo );
	switch ( nh ){
		case 0:
			ordenamiento();
			break;
		case 1:
			obtener_promedio();
			break;
		case 2:
			numeros_pares();
			break;
		case 3:
			numeros_primos();
			break;
		default:
			break;
	}
	pthread_mutex_unlock( &bloqueo );
	pthread_exit( arg );
}

