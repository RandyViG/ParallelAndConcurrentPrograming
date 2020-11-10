#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_HILOS 4
#define N 16

int *A, suma = 0;
pthread_mutex_t bloqueo;

void * funHilo( void *arg );
void imprimirArreglo( int *datos);
void llenarArreglo( int *datos );
int * reservarMemoria( void );

int main( void ){
	int *hilo, nhs[NUM_HILOS];
    	pthread_t tids[NUM_HILOS];
    	register int nh;
	//srand( getpid() );

	A = reservarMemoria();
	
	llenarArreglo( A );

	printf("\nArreglo A:\n");
	imprimirArreglo( A );

	pthread_mutex_init( &bloqueo, NULL );

    	printf("\nProbando hilos..\n");
    	
	for( nh=0; nh < NUM_HILOS; nh++ ){
        	nhs[nh] = nh;
        	pthread_create( &tids[nh], NULL, funHilo, (void*)&nhs[nh] );
    	}
    
    	for( nh=0; nh < NUM_HILOS; nh++ ){
        	pthread_join( tids[nh], (void**)&hilo );
            	printf("El hilo %d termino \n", *hilo);
    	}
	printf("El promedio es: %d\n", suma>>4);	
	free( A );

    	return 0;
}

void * funHilo( void *arg ){
	register int i;
    	int nucleo = *(int*)arg;
	int suma_parcial = 0;
	printf("Hilo %d en ejecución \n", nucleo);
	for( i = nucleo ; i < N ; i += NUM_HILOS )
		suma_parcial +=  A[i];

	pthread_mutex_lock( &bloqueo );
	suma += suma_parcial;
	pthread_mutex_unlock( &bloqueo );
    
    	pthread_exit( arg );
}

int * reservarMemoria( void ){
	int *mem;
	mem = (int*) malloc( N * sizeof(int) );
	if( !mem ){
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo( int *datos ){
	register int i;
	for( i = 0; i < N ; i++ )
		datos[i] = rand() % 256;
}

void imprimirArreglo( int *datos){
	register int i;
	for( i = 0 ; i < N ; i++ ){
		if( !(i%16) && (i!=0) )
			printf("\n");
		printf("%3d ", datos[i]);
	}
	printf("\n");	
}

