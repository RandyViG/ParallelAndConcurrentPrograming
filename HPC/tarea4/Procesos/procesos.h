#ifndef PROCESOS_H
#define PROCESOS_H

#include"defs.h"

void procesoPadre( int pipefd[NUM_PROC][2], float *resultado );
void procesoHijo( int np, float *resultado, float *pulso, float *hann, int pipefd[] );

#endif
