#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"hilos.h"
#include"helper.h"
#include"defs.h"

int * datos, promedio, pares, primos;
pthread_mutex_t bloqueo;

int main( void ){
	int *hilo,nhs[NUM_HILOS];
    pthread_t tids[NUM_HILOS];
    register int nh;
	//srand( getpid() );
    	
	printf("\n\t\t\t... Tarea 3: Hilos ...\n");
    datos = reservarMemoria();
	llenarArreglo( datos );
	printf("Arreglo generado:\n");
	imprimirArreglo( datos );

	pthread_mutex_init( &bloqueo , NULL );

	for (nh=0;nh<NUM_HILOS;nh++){
        nhs[nh] = nh;
        pthread_create( &tids[nh], NULL, funHilo, (void*)&nhs[nh]);
    }
    
    for (nh=0;nh<NUM_HILOS;nh++){
        pthread_join( tids[nh], (void**)&hilo );
		printf("\nTermino el hilo: %d\n", *hilo);
        if( *hilo==0 ){
           	printf("Los datos ordenado son:\n");
			imprimirArreglo( datos );
		}
		else if( *hilo== 1 )
            printf("El promedio es: %d\n", promedio);
		else if( *hilo == 2)
            printf("El total de numeros pares es: %d\n", pares);
		else if( *hilo == 3 )
            printf("El total de numeros primos es:  %d\n", primos);
	}
	pthread_mutex_destroy( &bloqueo );
	free( datos );
	
    return 0;
}

