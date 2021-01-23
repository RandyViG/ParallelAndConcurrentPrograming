#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"defs.h"
#include"hilos.h"
#include"helper.h"

int *A, *B, producto_punto;
pthread_mutex_t bloqueo;

int main( void ){
	int *hilo, nhs[NUM_HILOS];
	pthread_t tids[NUM_HILOS];
	register int nh;
	producto_punto = 0;

	printf("\n\t\t... Tarea 5: Producto Punto ...\n");
	A = reservar_memoria();
	B = reservar_memoria();
	llenar_arreglo( A );
	llenar_arreglo( B );

	pthread_mutex_init( &bloqueo, NULL );
	
	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, fun_hilo, (void*)&nhs[nh] );
	}

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh], (void**)&hilo );
		printf("\nEl hilo %d termino \n", *hilo);
	}

	printf("\nProducto punto es: %d\n", producto_punto);
	
	pthread_mutex_destroy( &bloqueo );
	free( A );
	free( B );

	return 0;
}

