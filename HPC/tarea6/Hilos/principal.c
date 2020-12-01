#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"defs.h"
#include"hilos.h"
#include"helper.h"
#include"archivos.h"
#include"procesamiento.h"

float *pulso, *hann, *producto, *resultado, *seno;

int main( void ){
	int *hilo, nhs[NUM_HILOS];
	pthread_t tids[NUM_HILOS];
	register int nh;

	printf("\n\t\t\t... Tarea 6: Algoritmo de Ventaneo ...\n");
	pulso = reservar_memoria();
	hann = reservar_memoria();
	producto = reservar_memoria();
	resultado = reservar_memoria();

	leer_archivo( pulso , "../PulseSensor.dat" );
	ventana_hann();
	
	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, fun_hilo, (void*)&nhs[nh] );
	}

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh], (void**)&hilo );
		printf("\nEl hilo %d termino \n", *hilo);
	}
	
	guardar_archivo( hann, "ventanaHann.dat" );
	guardar_archivo( producto, "producto.dat" );

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, autocorrelacion, (void*)&nhs[nh] );
	}

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh], (void**)&hilo );
		printf("\nEl hilo %d termino \n", *hilo);
	}
	
	guardar_archivo( resultado, "resultado.dat" );
	
	free( hann );
	free( pulso );
	free( producto );
	free( resultado );
    	
	return 0;
}

