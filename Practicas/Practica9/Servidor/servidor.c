#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include"defs.h"
#include"procesamiento.h"
#include "imagen.h"
extern int sockfd;
extern unsigned char * imagen,* imagenGris,*imagenS;
extern uint32_t width_g,height_g;

void ini_servidor( struct sockaddr_in * direccion_servidor ){
	memset( direccion_servidor, 0, sizeof(struct sockaddr_in) );
	direccion_servidor->sin_family = AF_INET;
	direccion_servidor->sin_port = htons(PUERTO);
	direccion_servidor->sin_addr.s_addr = INADDR_ANY;

	printf("Creando Socket ....\n");
	if( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		perror("Ocurrio un problema en la creacion del socket\n");
		exit( EXIT_FAILURE );
	}
	printf("Configurando socket ...\n");
	if( bind( sockfd, (struct sockaddr *)direccion_servidor, sizeof(struct sockaddr_in) ) < 0 ){
		perror ("Ocurrio un problema al configurar el socket\n");
		exit(EXIT_FAILURE );
	}
	printf("Estableciendo la aceptacion de clientes...\n\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit( EXIT_FAILURE );
	}
}

void atiende_cliente( int cliente_sockfd){
	bmpInfoHeader info;
	int *hilo,nhs[NUM_HILOS], ss;
	pthread_t tids[NUM_HILOS]; 
	register int nh;
	
	printf("\nSe aceptó un cliente, atendiendolo \n");
	ss = system("raspistill -n -t 500 -e bmp -w 640 -h 480 -o foto.bmp ");
	printf("\nTermino system con estadoi: %d \n", ss);
	
	imagen = abrirBMP("foto.bmp",&info);
	displayInfo(&info);
	
	width_g=info.width;
	height_g=info.height;
	
	imagenGris = reservar_memoria(info.width,info.height);
	imagenS = reservar_memoria(info.width,info.height);
	memset(imagenGris,255,info.width*info.height);
	
	RGBToGray(imagen,imagenGris,info.width,info.height);

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, funHilo, &nhs[nh] );
	}

	for( nh = 0 ; nh < NUM_HILOS ; nh++ ){
		pthread_join( tids[nh],  (void **)&hilo);
		printf("Termino el hilo %d\n", *hilo ); 
	}

	if( write(cliente_sockfd,&info, sizeof(bmpInfoHeader)) < 0 ){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit( EXIT_FAILURE );
	}

	if( write(cliente_sockfd, imagenS, info.width*info.height) < 0 ){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit( EXIT_FAILURE );
	}

	free( imagen );
	free( imagenS );
	free( imagenGris );
	
	close( cliente_sockfd );
	exit( 0 );
}
