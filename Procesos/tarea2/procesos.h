#ifndef PROCESOS_H
#define PROCESOS_H

#include"defs.h"

void procesoPadre( int pipefd[NUM_PROC][2] );
void procesoHijo( int np, int *datos, int pipefd[] );

#endif
