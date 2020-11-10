#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include"defs.h"
#include"helper.h"
#include"archivos.h"
#include"procesos.h"
#include"procesamiento.h"

int main( void ){
	pid_t pid;
	register int np;
	int edo_pipe, pipefd[NUM_PROC][2];
	float *pulso, *hann, *resultado;

	printf("\n\t\t\t... Tarea 4: Algoritmo de Ventaneo ...\n");
	pulso = reservar_memoria();
	hann = reservar_memoria();
	resultado = reservar_memoria();

	leer_archivo( pulso, "../PulseSensor.dat" );
	ventana_hann( hann );
	
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
			procesoHijo( np , resultado, pulso, hann, pipefd[np] );
	}
	procesoPadre( pipefd, resultado );
	
	guardar_archivo( hann, "ventanaHann.dat" );
	guardar_archivo( resultado, "resultado.dat" );

	free( pulso );
	free( hann );
	free( resultado );

	return 0;
}
