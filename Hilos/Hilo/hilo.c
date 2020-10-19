#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int num1 = 20, num2 = 4;
void * suma( void * args );
void * resta( void * args );
void * multiplicacion( void * args );
void * division( void * args );

int main( void ){
	int *res_suma, *res_resta, *res_divi, *res_multi;;	
	pthread_t tid_suma, tid_resta, tid_multi, tid_divi;
	printf("Probando hilos...\n");
	
	pthread_create( &tid_suma, NULL , suma, NULL );
	pthread_create( &tid_resta, NULL , resta, NULL );
	pthread_create( &tid_multi, NULL , multiplicacion, NULL );
	pthread_create( &tid_divi, NULL , division, NULL );
	
	pthread_join( tid_suma, (void**)&res_suma );
	pthread_join( tid_resta, (void**)&res_resta );
	pthread_join( tid_multi, (void**)&res_multi );
	pthread_join( tid_divi, (void**)&res_divi );

	printf("La suma es: %d\n", *res_suma);
	printf("La resta es: %d\n", *res_resta);
	printf("La multiplicacion es: %d\n", *res_multi);
	printf("La division es: %d\n", *res_divi);

	free( res_multi );

	return 0;
}

void * suma( void * args ){
	static int res;
	res = num1 + num2;
	pthread_exit( (void*)&res );
}

void *  resta( void * args ){
	static int res;
	res = num1 - num2;
	pthread_exit( (void*)&res );
}

void * multiplicacion( void * args ){
	int *res = (int *)malloc( sizeof(int) );
	*res = num1 * num2;
	pthread_exit( (void*)res );
}

void * division( void * args ){
	static int res;
	res = num1 / num2;
	pthread_exit( (void*)&res );
}
