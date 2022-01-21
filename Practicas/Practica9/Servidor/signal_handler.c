#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

extern int sockfd;
extern unsigned char *imagen, *imagenGris,*imagenS;
void manejador( int sig ){
	int estado;
	pid_t pid;

	if( sig == SIGCHLD ){
		printf("\nSe recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso: %d con estado: %d\n", pid, estado>>8);
	}
	else if( sig == SIGINT ){
		printf("\nSe recibio la señal SIGINT en el servidor\n");
		printf("Concluimos la ejecución de la aplicacion Servidor \n");
		
		close( sockfd );
		exit( 0 );
	}

}

void ini_signals( void ){
	if( signal( SIGCHLD, manejador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGINT, manejador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
}
