#ifndef SERVIDOR_H
#define SERVIDOR_H

void atiende_cliente( int cliente_sockfd);
void ini_servidor( struct sockaddr_in * direccion_servidor );

#endif