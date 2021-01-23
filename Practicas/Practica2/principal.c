#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include"procesos.h"
#include"helper.h"
#include"defs.h"

int main( void ){
	pid_t pid;
	register int np;
	int *datos, edo_pipe, pipefd[NUM_PROC][2];
	
	printf("\n\t\t\t... Tarea 2: Procesos con pipes ...\n");	
	srand( getpid() );
	datos = reservarMemoria();
	llenarArreglo( datos );
	printf("\nArreglo generado:\n");
	imprimirArreglo( datos );
	
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
			procesoHijo( np , datos, pipefd[np] );
	}
	procesoPadre( pipefd );
	free( datos );

	return 0;
}
