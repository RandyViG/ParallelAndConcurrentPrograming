#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include"defs.h"

extern unsigned char *imagenRGB, *imagenGray, *imagenS;

void * sobel( void *args ){
	register int x, y, ym, xm;
	int nucleo, eleBloque, inicio, fin;
	int indicei, indicem, convFil, convCol;
	struct params *parametros = (struct params *)args;
 
	int gradienteFila[ DIMASK * DIMASK ] = {
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	};
	int gradienteColumna[DIMASK * DIMASK] = {
		-1, -2, -1,
		 0,  0,  0,
		 1,  2,  1
	};

 	nucleo = parametros->nh;
	eleBloque = parametros->height / NUM_HILOS;
	inicio = nucleo * eleBloque;
	fin = inicio + eleBloque;
	fin = ( nucleo == NUM_HILOS - 1 ) ? fin - DIMASK : fin;
	
	for( y = inicio ; y <= fin ; y++ )
    		for( x = 0 ; x <= ( parametros->width - DIMASK ) ; x++ ){
        		indicem = 0;
         	convFil = 0;
				convCol = 0;
            for( ym = 0 ; ym < DIMASK ; ym++ )
            	for( xm = 0; xm < DIMASK ; xm++ ){
               	indicei = (y+ym) * parametros->width + (x+xm);
                  convFil += imagenGray[indicei] * gradienteFila[indicem];
                  convCol += imagenGray[indicei] * gradienteColumna[indicem++];
               }
            convFil = convFil >> 2;
            convCol = convCol >> 2;
            indicei = (y+1) * parametros->width + (x+1);
            imagenS[indicei] = (unsigned char) sqrt( (convFil*convFil) + (convCol*convCol) );
        	}

	pthread_exit( (void*)&parametros->nh );
}
