#include<stdio.h>
#include<pthread.h>
#include"defs.h"

extern unsigned char *imagenRGB, *imagenGray, *imagenFiltrada;

void * filtroPB( void *args ){
	register int x, y, ym, xm;
	int nucleo, eleBloque, inicio, fin;
	int indicei, indicem, conv, factor = 330;
	struct params *parametros = (struct params *)args;
    int kernelGaussiano[DIMASK*DIMASK] = {
    	1, 4,  7,  4,  1,
        4, 20, 33, 20, 4,
        7, 33, 54, 33, 7,
        4, 20, 33, 20, 4,
        1, 4,  7,  4,  1
    };
 
 	nucleo = parametros->nh;
	eleBloque = parametros->height / NUM_HILOS;
	inicio = nucleo * eleBloque;
	fin = inicio + eleBloque;
	fin = (fin == parametros->height) ? parametros->height - DIMASK : fin;
	for( y = inicio ; y <= fin ; y++ )
    	for( x = 0 ; x <= ( parametros->width - DIMASK ) ; x++ ){
        	indicem = 0;
            conv = 0;
            for( ym = 0 ; ym < DIMASK ; ym++ )
            	for( xm = 0; xm < DIMASK ; xm++ ){
                	indicei = (y+ym) * parametros->width + (x+xm);
                    conv += imagenGray[indicei] * kernelGaussiano[indicem++];
                }
            conv /= factor;
            indicei = (y+1) * parametros->width + (x+1);
            imagenFiltrada[indicei] = conv;
        }
	pthread_exit( (void*)&parametros->nh );
}
