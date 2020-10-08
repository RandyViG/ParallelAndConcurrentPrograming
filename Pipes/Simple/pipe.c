#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define NUM_PROC 4 

void proceso_padre( int pipefd[] );
void proceso_hijo( int np , int pipefd[] );

int main( void ){
	pid_t pid;
	register int np;
	int pipefd[2], edo_pipe;
	
	printf("Probando procesos...\n");
	edo_pipe = pipe( pipefd );
	if( edo_pipe == -1 ){
		perror("Error al crear la tuberia...\n");
		exit(EXIT_FAILURE);
	}

	for(np = 0; np < NUM_PROC ; np++){
		pid =fork();
		if( pid == -1 ){
			perror("Eror al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid  )
			proceso_hijo( np , pipefd );
	}
	proceso_padre( pipefd );

	return 0;
}

void proceso_padre( int pipefd[] ){
	pid_t pid;
	int estado, numproc, result;
	register int np;
	close( pipefd[1] );

	for( np = 0; np < NUM_PROC ; np++){
		pid = wait(&estado);
		numproc = estado >> 8;
		read( pipefd[0] , &result, sizeof(int) );
		printf("Termino el proceso %d \n",numproc);

		if( numproc == 0  )
			printf("La suma es: %d\n", result);
		else if( numproc == 1 )
			printf("La resta es: %d\n",result);
		else if( numproc == 2 )
			printf("La multiplicación es: %d\n", result);
		else if( numproc == 3 )
			printf("La división es: %d\n", result);
	}
}

void proceso_hijo( int np , int pipefd[] ){
	int num1 = 20, num2 = 4;
	int result;
	close( pipefd[0] );

	if( np == 0 )
		result = num1 + num2;
	else if( np == 1)
		result = num1 - num2;
	else if( np == 2 )
		result = num1 * num2;
	else if( np == 3 )
		result = num1 / num2;	

	write( pipefd[1] , &result , sizeof(int) );
	close( pipefd[1] );	
	exit( np );
}
