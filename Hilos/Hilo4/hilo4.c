#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_HILOS 4

void * funHilo( void *arg );

int contador;
pthread_mutex_t bloqueo;

int main( void ){
	int *hilo, nhs[NUM_HILOS];
    	pthread_t tids[NUM_HILOS];
    	register int nh;
	contador = 0;

    	printf("Probando hilos...\n");
    	
	pthread_mutex_init( &bloqueo, NULL );

	for( nh=0; nh<NUM_HILOS; nh++ ){
        	nhs[nh] = nh;
        	pthread_create( &tids[nh], NULL, funHilo, (void*)&nhs[nh] );
    	}
    	
	for( nh=0; nh<NUM_HILOS; nh++ ){
        	pthread_join( tids[nh], (void**)&hilo );
        	printf("El hijo %d termino...\n", *hilo);
	}
	pthread_mutex_destroy( &bloqueo );

    	return 0;
}

void * funHilo( void *arg ){
    	int nh = *(int*)arg;
	register int i = 0;

	pthread_mutex_lock( &bloqueo );
	
	contador++; 
    	printf("Hilo %d en ejecucion con contador: %d\n",nh,contador);
	//sleep( 1 ); funcion no reentrante
    	while( (--i) );
	contador++;
	printf("Hilo %d en ejecucion con contador: %d\n",nh,contador);	
	
	pthread_mutex_unlock( &bloqueo );
    	
	pthread_exit( arg );
}
