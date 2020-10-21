#ifndef HELPER_H
#define HELPER_H

int * reservarMemoria( void );
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos);
void enviarArreglo( int *datos, int pipefd[] );
void recibirArreglo( int pipefd[] );

#endif
