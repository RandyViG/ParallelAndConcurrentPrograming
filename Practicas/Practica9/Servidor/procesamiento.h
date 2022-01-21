#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H
#include <stdint.h>
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
unsigned char * reservar_memoria( uint32_t width, uint32_t height );
void * funHilo(void *arg);

#endif
