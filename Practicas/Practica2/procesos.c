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
	int estado, numproc, result, *datos;
	register int np;
	datos = reservarMemoria();

	for( np = 0 ; np  < NUM_PROC ; np++ ){
		close( pipefd[np][1] );
		pid = wait( &estado );
		numproc = estado >> 8;
		
		printf("\nTermino el proceso %d con pid: %d\n", numproc, pid);

		if( numproc == 0 ){
			read( pipefd[numproc][0] , datos , sizeof(int)*N );
			printf("Los datos ordenados son:\n");
			imprimirArreglo( datos );
		}
		else if( numproc == 1 ){
			read( pipefd[numproc][0] , &result , sizeof(int) );
			printf("El promedio es: %d\n", result);
		}
		else if( numproc == 2 ){
			read( pipefd[numproc][0] , &result , sizeof(int) );
			printf("El total de numeros pares es: %d\n", result);
		}
		else if( numproc == 3 ){
			read( pipefd[numproc][0] , datos , sizeof(int)*N );
			printf("Los datos multiplicados son:\n");
			imprimirArreglo( datos );
		}

		close( pipefd[numproc][0] );
	}
	free( datos );
}

void procesoHijo( int np, int *datos, int pipefd[] ){
	int result;
	close( pipefd[0] );

	if( np == 0 ){
		ordenamiento( datos );
		write( pipefd[1], datos, sizeof(int)*N );
	}
	else if( np == 1 ){
		result = promedio( datos );
		write( pipefd[1], &result, sizeof(int) );
	}	
	else if( np == 2){
		result = numerosPares( datos );
		write( pipefd[1], &result, sizeof(int) );
	}
	else if( np == 3 ){
		multiplicarDatos( datos );
		write( pipefd[1], datos, sizeof(int)*N );
	}
	
	free( datos );
	close( pipefd[1] );
	exit( np );
}
