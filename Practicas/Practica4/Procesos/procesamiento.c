#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include"defs.h"

void generar_seno( float *datos ){
	float f=1000, fs=45000;
	register int n;
	
	for(n = 0; n < N ; n++)
		datos[n] = sinf( 2*M_PI*f*n/fs );
}

void ventana_hann( float *datos ){
	float a0, a1;
	a0 = a1 = 0.5;
	register int n;

	for( n = 0 ; n < N ; n++ )
		datos[n] = a0 - (a1 * cosf( (2*M_PI*n)/(N-1) ));
}
