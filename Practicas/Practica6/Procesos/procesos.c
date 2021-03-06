#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include"helper.h"
#include"procesamiento.h"
#include"defs.h"

void procesoPadre( int pipefd[NUM_PROC][2], float *datos ){
	pid_t pid;
	int estado, numproc, inicio, elemBloque;
	register int np;
	elemBloque = N / NUM_PROC;

	for( np = 0 ; np  < NUM_PROC ; np++ ){
		close( pipefd[np][1] );
		pid = wait( &estado );
		numproc = estado >> 8;
		inicio = elemBloque * numproc;
		printf("\nTermino el proceso %d con pid: %d\n", numproc, pid);
		read( pipefd[numproc][0], datos + inicio, sizeof(float)*elemBloque );
		close( pipefd[numproc][0] );
	}
}

void procesoHijo( int np, float *producto, float *pulso, float *hann, int pipefd[] ){
	int inicio, fin, elemBloque;
	register int i;
	elemBloque = N / NUM_PROC;
	inicio = np *  elemBloque;
	fin = inicio + elemBloque;
	close( pipefd[0] );
	
	for( i = inicio ; i < fin ; i++ )
		producto[i] = pulso[i] * hann[i];

	write( pipefd[1], producto + inicio, sizeof(float)*elemBloque );
	
	free( producto );
	free( pulso );
	free( hann );

	close( pipefd[1] );
	exit( np );
}

void autocorrelacion( int np, float *resultado, float *producto, int pipefd[] ){
	int inicio, fin, elemBloque, suma;
	register int n, l;
	elemBloque = N / NUM_PROC;
	inicio = np *  elemBloque;
	fin = inicio + elemBloque;
	close( pipefd[0] );
	
	for( l = inicio ; l < fin ; l++ ){
		suma = 0;
		for( n = l ; n < N ; n++ )
			suma += producto[n] * producto[n-l];
		resultado[l] = suma;
	}

	write( pipefd[1], resultado + inicio, sizeof(float)*elemBloque );
	
	free( resultado );
	free( producto );

	close( pipefd[1] );
	exit( np );
}
