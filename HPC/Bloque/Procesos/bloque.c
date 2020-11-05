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

int *A, *B, *C;

int main( void ){
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	printf("Probando procesos con pipes...\n");
	
	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();
	
	llenarArreglo( A );
	llenarArreglo( B );
	
	imprimirArreglo( A );
	imprimirArreglo( B );

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
	imprimirArreglo( C );
	free( A );
	free( B );
	free( C );

	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] ){
	pid_t pid;
	int estado, numproc, inicio, elemBloque;
	register int np;

	elemBloque = N / NUM_PROC;
	for( np = 0; np < NUM_PROC ; np++){
		close( pipefd[np][1] );
		pid = wait(&estado);
		numproc = estado >> 8;
		inicio = elemBloque * numproc;
		
		read( pipefd[numproc][0] , C + inicio , sizeof(int) * elemBloque );
		printf("Termino el proceso %d con pid: %d \n",numproc,pid);
		
		close( pipefd[numproc][0] );
	}
}

void proceso_hijo( int np , int pipefd[] ){
	int inicio, fin, elemBloque;
	register int i;
	
	elemBloque = N / NUM_PROC;
	inicio = np * elemBloque;
	fin = inicio + elemBloque;

	close( pipefd[0] );

	for( i = inicio ; i < fin ; i++ )
		C[i] = A[i] * B[i];

	write( pipefd[1] , C + inicio , sizeof(int)*elemBloque );
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

