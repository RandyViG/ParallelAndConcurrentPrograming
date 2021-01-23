#include<stdio.h>
#include<stdlib.h>
#include"defs.h"

void guardar_archivo( float *datos, char *archivo){
	FILE *apArch;
	register int n;

	apArch = fopen(archivo, "w");
	if( apArch == NULL ){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for( n = 0 ; n < N ; n++ )
		fprintf(apArch, "%f\n",datos[n]);
	fclose( apArch );
}

void leer_archivo( float *datos, char *archivo ){
	FILE *apArch;
	register int n;
	apArch = fopen( archivo, "r");
	if( apArch == NULL ){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for( n = 0; n < N ; n++ ){
		fscanf(apArch, "%f\n", &datos[n]);
		datos[n] -= 2200;
	}
	fclose( apArch );
}
