#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define NUM_PROC 4 
#define N 16

void proceso_padre( int pipefd[NUM_PROC][2] );
void proceso_hijo( int np , int pipefd[] );
void llenarArreglo( int *datos );
int * reservarMemoria( void );
void imprimirArreglo( int *datos );

int *A;

int main( void ){
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	printf("Probando procesos con pipes...\n");
	
	A = reservarMemoria();
	llenarArreglo( A );
	imprimirArreglo( A );

	for(np = 0; np < NUM_PROC ; np++){
		edo_pipe = pipe( pipefd[np] );
		if( edo_pipe == -1 ){
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}
		pid =fork();
		if( pid == -1 ){
			perror("Eror al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid  )
			proceso_hijo( np , pipefd[np] );
	}
	proceso_padre( pipefd );
	free( A );

	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] ){
	pid_t pid;
	int estado, numproc, promedio = 0, aux;
	register int np;

	for( np = 0; np < NUM_PROC ; np++){
		close( pipefd[np][1] );
		pid = wait(&estado);
		numproc = estado >> 8;
		
		read( pipefd[numproc][0] , &aux , sizeof(int) );
		printf("Termino el proceso %d con pid: %d \n",numproc,pid);
		promedio += aux;
		close( pipefd[numproc][0] );
	}
	printf("El promedio es %d\n", promedio>>4);
}

void proceso_hijo( int np , int pipefd[] ){
	int suma = 0;
	register int i;
	
	close( pipefd[0] );

	for( i = np ; i < N ; i += NUM_PROC )
		suma += A[i];

	write( pipefd[1] , &suma , sizeof(int) );
	close( pipefd[1] );	
	exit( np );
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

void imprimirArreglo( int *datos ){
	register int i;
	for( i = 0 ; i < N ; i++ ){
		if( !(i%16) && (i!=0) )
			printf("\n");
		printf("%4d ", datos[i]);
	}
	printf("\n");	
}

