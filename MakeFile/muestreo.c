#include<stdio.h>
#include"procesamiento.h"
#include"archivos.h"
#include"defs.h"


int main( void ){
	float seno[ MUESTRAS ];
	generarSeno( seno );
	guardarDatos( seno );
	
	return 0;
}

