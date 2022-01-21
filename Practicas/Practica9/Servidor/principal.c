#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"defs.h"
#include"servidor.h"
#include"signal_handler.h"

int sockfd;
unsigned char *imagen, *imagenGris,*imagenS;
uint32_t width_g,height_g;
int main(int argc, char **argv){
	int cliente_sockfd;
	struct sockaddr_in direccion_servidor;
	pid_t pid;
	
	ini_signals();
	ini_servidor( &direccion_servidor );

	for( ; EVER ;  ){
		printf("En espera de peticiones de conexión ...\n");
		if( ( cliente_sockfd = accept(sockfd, NULL, NULL) ) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit( EXIT_FAILURE );
		}
		pid = fork();
		if( !pid )
			atiende_cliente( cliente_sockfd );
	}
	
	return 0;
}
