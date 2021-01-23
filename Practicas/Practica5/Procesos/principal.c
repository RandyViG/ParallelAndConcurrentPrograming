#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include"defs.h"
#include"helper.h"
#include"procesos.h"

int main( void ){
	pid_t pid;
	register int np;
	int edo_pipe, pipefd[NUM_PROC][2];
	int *A, *B;

	printf("\n\t\t... Tarea 5: Producto Punto ...\n");
	A = reservar_memoria();
	B = reservar_memoria();
	llenar_arreglo( A );
	llenar_arreglo( B );
	
	for( np = 0; np < NUM_PROC ; np++ ){
		edo_pipe = pipe( pipefd[np] );
		if( edo_pipe == -1 ){
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if( pid == -1 ){
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid )
			proceso_hijo( np , A, B, pipefd[np] );
	}
	proceso_padre( pipefd );
	
	free( A );
	free( B );

	return 0;
}
