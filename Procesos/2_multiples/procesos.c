#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define NUM_PROC 2 
#define N 32
#define EVER 1

void proceso_padre( void );
void proceso_hijo( int np , int *datos );
int * reservarMemoria( void );
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos);
int buscarMayor( int *datos );
int buscarMenor( int *datos );

int main( void ){
	pid_t pid;
	register int np;
	int *datos;
	
	printf("Probando procesos...\n");
	srand( getpid()  );
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	
	for(np = 0; np < NUM_PROC ; np++){
		pid =fork();
		if( pid == -1 ){
			perror("Eror al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid  )
			proceso_hijo( np , datos );
	}
	proceso_padre();
	free( datos );

	return 0;
}

void proceso_padre( void ){
	pid_t pid;
	int estado;
	register int np;
	for( np = 0; np < NUM_PROC ; np++){
		pid = wait(&estado);
		printf("Proceso hijo %d con retorno: %d\n",pid,estado>>8);
	}
}

void proceso_hijo( int np , int *datos ){
	int mayor,menor;
	if( np == 0 ){
		mayor = buscarMayor( datos );
		exit( mayor );
	}
	else if( np == 1){
		menor = buscarMenor( datos );
		exit( menor );
	}
}

int * reservarMemoria( void ){
	int *mem; 
	mem = (int *) malloc( N *sizeof(int) );
	if( !mem  ){
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	return mem;
}

void llenarArreglo( int *datos ){
	register int i;
	for( i = 0 ; i < N ; i++ )
		datos[i] = rand() % 256;
}

void imprimirArreglo( int *datos ){
	register int i;
	for( i = 0; i < N ; i++ ){
		if( !(i%16) )
			printf("\n");
		printf("%3d ",datos[i]);
	}
	printf("\n");
}

int buscarMayor( int *datos ){
	int mayor = datos[0];
	register int i;
	for( i = 1 ; i < N ; i++ )
		if( datos[i] > mayor )
			mayor = datos[i];
	
	return mayor;
}
int buscarMenor( int *datos){
	int menor = datos[0];
	register int i;
	for( i = 1 ; i < N ; i++ )
		if( datos[i] < menor )
			menor = datos[i];
	
	return menor;
}

