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
	int *datos;
	
	srand( getpid() );
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	
	for( np = 0; np < NUM_PROC ; np++ ){
		pid = fork();
		if( pid == -1 ){
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid )
			procesoHijo( np , datos );
	}
	procesoPadre();
	free( datos );

	return 0;
}
