#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_HILOS 4
#define N 16

int *A, *B, *C;

void * funHilo( void *arg );
void imprimirArreglo( int *datos);
void llenarArreglo( int *datos );
int * reservarMemoria( void );

int main( void ){
	int *hilo, nhs[NUM_HILOS];
    	pthread_t tids[NUM_HILOS];
    	register int nh;
	srand( getpid() );

	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();
	
	llenarArreglo( A );
	llenarArreglo( B );

	printf("\nArreglo A:\n");
	imprimirArreglo( A );
	printf("\nArreglo B:\n");
	imprimirArreglo( B );

    	printf("\nProbando hilos..\n");
    	
	for( nh=0; nh < NUM_HILOS; nh++ ){
        	nhs[nh] = nh;
        	pthread_create( &tids[nh], NULL, funHilo, (void*)&nhs[nh] );
    	}
    
    	for( nh=0; nh < NUM_HILOS; nh++ ){
        	pthread_join( tids[nh], (void**)&hilo );
            	printf("El hilo %d termino \n", *hilo);
    	}

	printf("\nArreglo C:\n");
	imprimirArreglo( C );
	
	free( A );
	free( B );
	free( C );

    	return 0;
}

void * funHilo( void *arg ){;
	register int i;
    	int nucleo = *(int*)arg;

	printf("Hilo %d en ejecución \n", nucleo);
	
	for( i = nucleo ; i < N ; i += NUM_HILOS )
		C[i] =  A[i] * B[i];
    
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

