#ifndef PROCESOS_H
#define PROCESOS_H

#include"defs.h"

void proceso_padre( int pipefd[NUM_PROC][2] );
void proceso_hijo( int np, int *A, int *B, int pipefd[] );

#endif
