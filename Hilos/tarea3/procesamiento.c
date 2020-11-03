#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include"defs.h"

extern int * datos, promedio, pares, primos;

void ordenamiento( void ){
	int aux;
	register int i,j;
	for( i = 0 ; i < N ; i++ )
		for( j = 0 ; j < N-1 ; j++ )
			if( datos[j] > datos[j+1] ){
				aux = datos[j+1];
				datos[j+1] = datos[j];
				datos[j] = aux;
			}
}

void obtener_promedio( void ){
	promedio = 0;
	register int i;
	for( i = 0 ; i < N ; i++ )
		promedio += datos[i];
	promedio = promedio / N;
}

void numeros_pares( void ){
	pares = 0;
	register int i;
	for( i = 0 ; i < N ; i++ )
	    if( datos[i]%2 == 0 )
			pares++;
}

void numeros_primos( void ){
	register int i, j;
	primos = 0;
	for( i = 0 ; i < N ; i++ ){
		j = 2;
		if( ( datos[i] % 2 == 0 ) && ( datos[i] != 2 ) ) 
			continue;
		
		while( ( datos[i] % j != 0 ) && ( j++ < datos[i] ) );
		
		if( j == datos[i] )
			primos++;
	}
}
