/*

EJERCICIO 1: a

Crear un abanico de procesos

*/

#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>

#include <unistd.h>

#include <errno.h>

#include <sys/wait.h>

int main( int argc, char *argv[] )
{

	pid_t pid, chilpid;

	int status ,N;

	printf(" Numero de hijos: ");

	scanf("%d",&N);

	for(int i=0 ; i<N; i++)
	{

		pid = fork();

		switch(pid)
		{
			
			// Caso error

			case -1: 

				perror("fork error");
	
				printf("errno value = %d\n", errno);
	
				exit(EXIT_FAILURE); //retorna 1

			// Caso hijo

			case 0:

				printf(" Soy el hijo %d. Proceso : %d. Mi padre = %d\n", i+1, getpid(), getppid() );

				exit(EXIT_SUCCESS);

		}

	}

	printf(" Proceso padre %d; mi padre %d\n", getpid(), getppid() );

	for(int i=0 ; i<N; i++)
	{

		chilpid = wait(&status);

		if(chilpid > 0)
		{

			if(WIFEXITED(status)) printf("child %d exited, status = %d\n", chilpid, WEXITSTATUS(status));

			else if (WIFSIGNALED(status)) printf("child %d killed (signal %d)\n", chilpid, WTERMSIG(status));
	 
			else if (WIFSTOPPED(status)) printf("child %d stopped (signal %d)\n", chilpid, WSTOPSIG(status));

		}

		else 
		{

		     	   printf(" Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");

		 	   exit(EXIT_FAILURE);
    		} 	

   	}

	exit(EXIT_SUCCESS);

}