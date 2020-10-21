#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_HILOS 4

void * funHilo( void * arg );

int num1 = 20, num2 = 4;

int main( void ){
	register int nh;
	int *res, nhs[ NUM_HILOS ];	
	pthread_t tids[ NUM_HILOS ];
	printf("Probando hilos...\n");
	
	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, funHilo, (void*)&nhs[nh] );
	}
	
	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh], (void**)&res );
		printf("El resultado es: %d \n", *res);
		free(res);
	}

	return 0;
}

void * funHilo( void * arg ){
	int nh = *(int*)arg;
	int *res = malloc( sizeof(int) );

	printf("Hilo %d en ejecución\n", nh);
	if( nh == 0 )
		*res = num1 + num2;
	else if( nh == 1 )
		*res = num1 - num2;
	else if( nh == 2 )
		*res = num1 * num2;
	else if( nh == 3 )
		*res = num1 / num2;

	pthread_exit( (void*)res );
}
