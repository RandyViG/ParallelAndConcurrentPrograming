#include<stdio.h>
#include<stdint.h>

void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height ){ 
	register int indiceGray; 
	int pixel; 
 
	for( indiceGray = 0 ; indiceGray < (height * width) ; indiceGray++ ){ 
    	pixel = imagenGray[indiceGray] + 70;          
		imagenGray[indiceGray] = (pixel > 255) ? 255 : (unsigned char) pixel;    
	} 
}

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int indiceGray, indiceRGB;
    unsigned char nivelGris;
    for( indiceGray = 0, indiceRGB = 0 ; indiceGray < ( height * width ) ; indiceGray++, indiceRGB += 3 ){
 		nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2])/100;
        imagenGray[indiceGray] = nivelGris;
    }
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int indiceGray, indiceRGB;
    
	for( indiceGray = 0, indiceRGB = 0 ; indiceGray < ( height * width ) ; indiceGray++, indiceRGB += 3 ){
    	imagenRGB[indiceRGB] = imagenGray[indiceGray];
        imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
        imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
     }
}

