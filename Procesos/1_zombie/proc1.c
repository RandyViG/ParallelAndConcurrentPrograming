#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main( void ){
	int status;
	float num1 = 45, num2 = 13, suma, resta;
	pid_t pid;
	printf("Probando procesos...\n");
	pid =fork();
	if( pid == -1 ){
		perror("Eror al crear el proceso...\n");
		exit(EXIT_FAILURE);
	}
	else if( !pid  ){
		printf("Proceso hijo ejecutado con pid %d...\n", getpid() );
		suma = num1 + num2;
		printf("Suma: %f\n", suma );
		exit(0);	
	}
	else{
		sleep(20);
		printf("Proceso padre ejecutado con pid %d...\n", getpid() );
		resta = num1 - num2;
		printf("Resta: %f\n", resta );
		pid = wait( &status );
		printf("Proceso terminado: %d con estado: %d\n", pid, status>>8);
	}

	return 0;
}
