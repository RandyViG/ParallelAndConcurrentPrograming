#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "imagen.h"

#define PUERTO 			5001	//Número de puerto asignado al servidor
#define COLA_CLIENTES 		5 	//Tamaño de la cola de espera para clientes
#define TAM_BUFFER 		100
#define EVER 			1

void manejador( int sig );
int finPrograma;
void atiendeCliente( int cliente_sockfd, unsigned char *imagenGray, bmpInfoHeader *info );
void iniServidor( );
void iniSignals( );
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
unsigned char * reservarMemoria( uint32_t width, uint32_t height );

int sockfd;
unsigned char *imagenRGB, *imagenGray;

int main(int argc, char **argv){
	pid_t pid;
   int cliente_sockfd;
   bmpInfoHeader info;

   imagenRGB = abrirBMP("../../../ProcesamientoImagen/Imagenes/huella1.bmp", &info );

   displayInfo( &info );
   imagenGray = reservarMemoria( info.width, info.height );
   RGBToGray( imagenRGB, imagenGray, info.width, info.height );

	finPrograma = 0;
	iniSignals( );
	iniServidor( );

	for( ; EVER ; ){
	   printf ("En espera de peticiones de conexión ...\n");
   	if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
   	}
		pid = fork();
		if( !pid )
			atiendeCliente( cliente_sockfd, imagenGray, &info );
	
	}

	return 0;
}

void iniSignals( ){
	if( signal( SIGCHLD, manejador) == SIG_ERR ){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}

	if( signal( SIGINT, manejador) == SIG_ERR ){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}
}

void iniServidor( ){
   struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion
   memset (&direccion_servidor, 0, sizeof (direccion_servidor));	//se limpia la estructura con ceros
   direccion_servidor.sin_family 		= AF_INET;
   direccion_servidor.sin_port 		= htons(PUERTO);
   direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;
   printf("Creando Socket ....\n");
   if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
   }
   printf("Configurando socket ...\n");
   if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 ){
		perror ("Ocurrio un problema al configurar el socket");
		exit(1);
   }
   printf ("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
   }

}

void atiendeCliente( int cliente_sockfd, unsigned char *imagenGray, bmpInfoHeader *info ){
	printf("Se aceptó un cliente, enviando Header imagen... \n");
	if( write(cliente_sockfd, info, sizeof(bmpInfoHeader) ) < 0 ){
		perror("Ocurrio un problema en el envio de la imagen");
		exit(EXIT_FAILURE);
	}

	printf("Se aceptó un cliente, enviando imagen... \n");
	if( write (cliente_sockfd, imagenGray, info->height * info->width) < 0 ){
		perror("Ocurrio un problema en el envio de la imagen");
		exit(EXIT_FAILURE);
	}

	close(cliente_sockfd);
	exit(0);
}

void manejador( int sig ){
	int estado;
	pid_t pid;

	if( sig == SIGCHLD ){
		printf("Se recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso %d con estado: %d\n", pid, estado>>8);
	}else if( sig == SIGINT ){
		printf("Se recibio la señal SIGINT en el servidor\n");
	   printf("Concluimos la ejecución de la aplicacion Servidor \n");
		finPrograma = 1;
		free( imagenRGB );
		free( imagenGray );
		close( sockfd );

		exit( 0 );
	}
}

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	unsigned char nivelGris;
   int indiceRGB, indiceGray;

   for( indiceGray = 0, indiceRGB = 0; indiceGray < (height*width); indiceGray++, indiceRGB += 3 ){
   	nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2]) / 100;
      imagenGray[indiceGray] = nivelGris;
   }
}

unsigned char * reservarMemoria( uint32_t width, uint32_t height ){
        unsigned char *imagen;

        imagen = (unsigned char *)malloc( width*height*sizeof(unsigned char) );
        if( imagen == NULL ){
                perror("Error al asignar memoria a la imagen");
                exit(EXIT_FAILURE);
        }

        return imagen;
}

