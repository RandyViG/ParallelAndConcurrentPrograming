#include<stdio.h>
#include<math.h>
#include"defs.h"

extern float *pulso, *hann, *resultado, *seno;

void generar_seno( void ){
	float f=1000, fs=45000;
	register int n;
	
	for(n = 0; n < N ; n++)
		seno[n] = sinf( 2*M_PI*f*n/fs );
}

void ventana_hann( void ){
	float a0, a1;
	a0 = a1 = 0.5;
	register int n;
	for( n = 0 ; n < N ; n++ )
		hann[n] = a0 - (a1 * cosf( (2*M_PI*n)/(N-1) ));
}
