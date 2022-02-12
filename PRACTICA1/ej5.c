/*

EJERCICIO 5

Cree una variable global de tipo entero inicializada a 0. Haga que cada hijo aumente en uno el valor de esa variable global.

El padre imprima el resultado final

*/

#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>

#include <unistd.h> 

#include <errno.h>

#include <sys/wait.h>

int valor = 0;

int main( int argc, char argv[])
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

			case -1: //caso error

				perror("fork error");

				printf(" Errno value = %d\n", errno);

				exit(EXIT_FAILURE);

			case 0: //hijo

					printf(" Soy el hijo %d. Proceso : %d. Mi padre = %d\n", i+1, getpid(), getppid() );

					valor++;
	
					exit(EXIT_SUCCESS);

		}

	}

	printf(" Proceso padre %d; mi padre %d\n", getpid(), getppid() );

	for(int i=0 ; i<N; i++)
	{

		chilpid = wait(&status);

		if(chilpid > 0)
		{

			valor++;

			if(WIFEXITED(status)) printf(" Child %d exited, status = %d\n", chilpid, WEXITSTATUS(status));

			else if (WIFSIGNALED(status)) printf(" Child %d killed (signal %d)\n", chilpid, WTERMSIG(status));
 
			else if (WIFSTOPPED(status)) printf(" Child %d stopped (signal %d)\n", chilpid, WSTOPSIG(status)); 
		}
		
		else 
		{

			printf(" Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");

		   	exit(EXIT_FAILURE);

	    	} 

	    	printf(" Hijo %d. Valor: %d\n", i+1, valor);	

	    }

	exit(EXIT_SUCCESS);

}