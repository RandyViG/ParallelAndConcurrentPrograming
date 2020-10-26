#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 4

void * funHilo( void *arg );

int res_suma,res_resta,res_multi,res_divi;
int num1=20,num2=4;

int main( void ){
	int *hilo,nhs[NUM_HILOS];
    	pthread_t tids[NUM_HILOS];
    	register int nh;
    	printf("Probando hilos..\n");
    	
	for (nh=0;nh<NUM_HILOS;nh++){
        	nhs[nh] = nh;
        	pthread_create(&tids[nh],NULL,funHilo,(void*)&nhs[nh]);
    	}
    
    	for (nh=0;nh<NUM_HILOS;nh++){
        	pthread_join(tids[nh],(void**)&hilo);
        	if(*hilo==0)
            		printf("La suma es %d\n",res_suma);
        	if(*hilo==1)
            		printf("La resta es %d\n",res_resta);
        	if(*hilo==2)
            		printf("La multiplicacion es %d\n",res_multi);
        	if(*hilo==3)
            		printf("La division es %d\n",res_divi);
    	}

    	return 0;
}

void * funHilo( void *arg ){
    	int nh = *(int*)arg;
    	
	printf("Hilo %d en ejecucion \n",nh);
    	
	if(nh==0)
        	res_suma = num1 + num2;
    	else if(nh==1)
        	res_resta = num1 - num2;
    	else if (nh==2)
        	res_multi = num1 * num2;
    	else if (nh==3)
        	res_divi = num1 / num2;
    
    	pthread_exit( arg );
}
