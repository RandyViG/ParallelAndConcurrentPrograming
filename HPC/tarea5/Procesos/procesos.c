#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include"helper.h"
#include"defs.h"

void proceso_padre( int pipefd[NUM_PROC][2] ){
	pid_t pid;
	int estado, numproc, producto_punto = 0, suma_parcial;
	register int np;

	for( np = 0 ; np  < NUM_PROC ; np++ ){
		close( pipefd[np][1] );
		pid = wait( &estado );
		numproc = estado >> 8;
		printf("\nTermino el proceso %d con pid: %d\n", numproc, pid);
		read( pipefd[numproc][0] , &suma_parcial , sizeof( int ) );
		producto_punto += suma_parcial;
		close( pipefd[numproc][0] );
	}

	printf("\nProducto punto es: %d\n", producto_punto);
}

void proceso_hijo( int np, int *A, int *B, int pipefd[] ){
	int suma = 0;
	register int i;
	close( pipefd[0] );

	for( i = np ; i < N ; i += NUM_PROC )
		suma += ( A[i] * B[i] );

	write( pipefd[1], &suma, sizeof( int ) );
	
	close( pipefd[1] );
	free( A );
	free( B );
	exit( np );
}
