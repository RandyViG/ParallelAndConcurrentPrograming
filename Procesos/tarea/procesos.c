#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"procesamiento.h"
#include"defs.h"

void procesoPadre( void ){
	pid_t pid;
	int estado;
	register int np;
	for( np = 0 ; np  < NUM_PROC ; np++ ){
		pid = wait(&estado);
		printf("Proceso hijo %d, con retorno %d\n",pid,estado>>8);
	}
}
void procesoHijo( int np, int *datos ){
	int resultado;
	if( np == 0 )
		resultado = buscarMayor( datos );
	else if( np == 1 )
		resultado = buscarMenor( datos );
	else if( np == 2)
		resultado = promedio( datos );
	else if( np == 3 )
		resultado = numerosPares( datos );

	exit( resultado );
}
