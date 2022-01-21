#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<netdb.h>
#include "imagen.h"

unsigned char * reservar_memoria( int tam );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void recibir_imagen( int sockfd, unsigned char *imagen, int tamImagen );
char * nslookup( char *hostname );

int main(int argc, char **argv){
	if( argc < 3 ){
		printf( "Uso: %s ip port\n", argv[0] );
		exit( 1 );
	}

	int sockfd, puerto;
	struct sockaddr_in direccion_servidor;
	unsigned char *imagen, *imagenRGB;
	bmpInfoHeader info;
	char *host;

	puerto = atoi( argv[2] );

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(puerto);
	
	host = nslookup( argv[1] );

	if( inet_pton(AF_INET, host, &direccion_servidor.sin_addr) <= 0 ){
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(1);
	}
	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}
	printf ("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) {
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}

	printf ("Recibiendo header del servidor ...\n");
	if (read (sockfd, &info, sizeof( bmpInfoHeader ) ) < 0){
		perror ("Ocurrio algun problema al recibir datos del servidor");
		exit(1);
	}
	displayInfo( &info );
	
	imagen = reservar_memoria( info.width * info.height );
	imagenRGB = reservar_memoria( info.width * info.height * 3 );

	recibir_imagen( sockfd, imagen, info.width * info.height );

	GrayToRGB( imagenRGB, imagen, info.width, info.height );
	
	guardarBMP("Servidor_Foto.bmp", &info, imagenRGB );

	printf("Cerrando la aplicacion cliente\n");
	close(sockfd);

	free( imagen );
	free( imagenRGB );

	return 0;
}

void recibir_imagen( int sockfd, unsigned char *imagen, int tamImagen ){
	int bytesRecibidos = 0, aux, tamLectura;
	tamLectura = tamImagen;
	
	printf ("Recibiendo header del servidor ...\n");
	while( bytesRecibidos < tamImagen ){
		aux = read(sockfd, imagen + bytesRecibidos, tamLectura );
		if( aux < 0 ){
			perror("Ocurrio algun problema al recibir datos del servidor");
			exit(1);
		}
		printf("\rBytes recibidos: %d", bytesRecibidos+=aux );
		tamLectura = tamImagen - bytesRecibidos;
	}
	printf("\n");
}

unsigned char * reservar_memoria( int tam ){
   unsigned char *imagen;
   
	imagen = (unsigned char *)malloc( tam * sizeof(unsigned char) );
   if( imagen == NULL ){
   	perror("Error al asignar memoria a la imagen");
      exit(EXIT_FAILURE);
  	}

   return imagen;
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
        register int x, y;
        int indiceGray, indiceRGB;
        for( y = 0 ; y < height ; y++ )
                for( x = 0 ; x < width ; x++ ){
                        indiceGray = y *  width + x;
                        indiceRGB = indiceGray * 3 ;
                        imagenRGB[indiceRGB] = imagenGray[indiceGray];
                        imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
                        imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
                }
}

char * nslookup( char *hostname ){
	struct addrinfo* res;
  	char* hostaddr;
  	struct sockaddr_in* saddr;
  
  	if ( getaddrinfo(hostname, NULL, NULL, &res) != 0 ) {
    	fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    	exit( EXIT_FAILURE );
  	}

  	saddr = (struct sockaddr_in*)res->ai_addr;
  	hostaddr = inet_ntoa(saddr->sin_addr);
  	printf("Dirección ip para %s es: %s\n", hostname, hostaddr);
	
	return hostaddr;
}
