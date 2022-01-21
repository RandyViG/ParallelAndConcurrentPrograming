#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<pthread.h>
#include <math.h>
#include"defs.h"

extern unsigned char *imagen, *imagenGris,*imagenS;
extern uint32_t width_g,height_g;

unsigned char * reservar_memoria( uint32_t width, uint32_t height ){
	unsigned char *imagenF;
	imagenF = (unsigned char *) malloc( width * height * sizeof( unsigned char ) );
	if( imagenF == NULL ){
		perror( "Error al asignar memoria a la imagen");
		exit( EXIT_FAILURE );
	}

	return imagenF;
}

void * funHilo(void *arg){
    int nucleo = *(int*)arg;//Numero de hilo q esta entrando a ejecutar el algoritmo
    int ele_x_bloque=height_g/NUM_HILOS; //Tamaño por bloque
    int iniBloque=nucleo*ele_x_bloque;
    int finBloque=iniBloque+ele_x_bloque;
    register int x,y,ym,xm;
	int indicei,indicem,convFila,convColumna,tope;
	int gradienteFila[DIMMASK*DIMMASK] = {
		1,0,-1,
		2,0,-2,
		1,0,-1
	};
	int gradienteColumna[DIMMASK*DIMMASK] = {
		-1,-2,-1,
		 0,0,0,
		 1,2,1
	};
	/*Validacion bordes*/
	
	if (nucleo==NUM_HILOS-1)
		tope=(finBloque)-DIMMASK;
	else	
		tope=finBloque;
	for (y=iniBloque;y<=tope;y++){
		for (x=0;x<=width_g-DIMMASK;x++){
			indicem=0;
			convFila = 0;
			convColumna = 0;
			for(ym=0;ym<DIMMASK;ym++){
				for(xm=0;xm<DIMMASK;xm++){
					indicei =(y+ym)*width_g+(x+xm);
					convFila += imagenGris[indicei]*gradienteFila[indicem];
					convColumna += imagenGris[indicei]*gradienteColumna[indicem++];
				}
			}
			convFila = convFila>>2; //Diviendo entre 4
			convColumna = convColumna>>2;
			
			indicei=(y+1)*width_g+(x+1);
			imagenS[indicei]=(unsigned char)sqrt((convFila*convFila)+(convColumna*convColumna));
		}
	}
    pthread_exit(arg);
}

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){

	int indiceGray, indiceRGB;
	unsigned char nivelGris;
    for( indiceGray = 0 , indiceRGB=0; indiceGray < (height*width) ; indiceRGB+=3,indiceGray++ ){
        nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2]) / 100;
        imagenGray[indiceGray] = nivelGris;
    }
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	int indiceGray, indiceRGB;
	for( indiceGray = 0 , indiceRGB=0; indiceGray < (height*width) ; indiceRGB+=3,indiceGray++ ){
		imagenRGB[indiceRGB] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
	}
}
