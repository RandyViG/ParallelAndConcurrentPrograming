#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include"helper.h"
#include"procesamiento.h"
#include"defs.h"

void procesoPadre( int pipefd[NUM_PROC][2] ){
	pid_t pid;
	int estado, numproc, result;
	register int np;

	for( np = 0 ; np  < NUM_PROC ; np++ ){
		close( pipefd[np][1] );
		pid = wait( &estado );
		numproc = estado >> 8;
		
		printf("\nTermino el proceso %d con pid: %d\n", numproc, pid);
		read( pipefd[numproc][0] ,&result , sizeof(int) );

		if( numproc == 0 ){
			printf("Los datos ordenados son:\n");
			printf("%4d ", result);
			recibirArreglo( pipefd[numproc] );
		}
		else if( numproc == 1 )
			printf("El promedio es: %d\n", result);
		else if( numproc == 2 )
			printf("El total de numeros pares es: %d\n", result);
		else if( numproc == 3 ){
			printf("Los datos multiplicados son:\n");
			printf("%4d ", result);
			recibirArreglo( pipefd[numproc] );
		}

		close( pipefd[numproc][0] );
	}
}

void procesoHijo( int np, int *datos, int pipefd[] ){
	int result;
	close( pipefd[0] );

	if( np == 0 ){
		ordenamiento( datos );
		enviarArreglo( datos, pipefd );
		exit( np );
	}
	else if( np == 1 )
		result = promedio( datos );
	else if( np == 2)
		result = numerosPares( datos );
	else if( np == 3 ){
		multiplicarDatos( datos );
		enviarArreglo( datos, pipefd  );
		exit( np );
	}
	
	write( pipefd[1], &result, sizeof(int) );
	
	close( pipefd[1] );
	exit( np );
}
