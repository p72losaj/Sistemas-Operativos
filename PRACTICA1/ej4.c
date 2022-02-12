/*

EJERCICIO 4

Cree un programa que reciba por la linea de argumentos un número y calcule el factorial de ese número.

Cree otro programa que reciba dos números enteros como parámetros en la linea de argumentos y 

Cree dos procesos hijos.  En el programa que calcula el factorial ponga un sleep(1).

*/

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <sys/wait.h>

#include <errno.h>

#include <sys/types.h>

#include <unistd.h>

long factorial(int n) 
{

	    if (n == 0) return 1;

	    return (n*factorial(n-1));

}

int main(int argc, char** argv)
{

	pid_t pid, childpid;

	int num, status;

	if(argc != 3)
	{

		printf(" Error de argumentos: ej4 valor1 valor2\n");

		exit(EXIT_FAILURE);

	}

	for(int i=0; i<2; i++)
	{

		pid = fork();

		switch(pid)
		{

			case -1: //caso error

			printf("fork error");

			printf(" Errno value: %d\n",errno);

			exit(EXIT_FAILURE);

			case 0: //hijos
	
			if(i==0)
			{
				printf(" Hijo 1. Pid proceso hijo: %d. Pid proceso padre: %d\n", getpid(), getppid()) ;

				printf(" Factorial de %d: %ld\n",atoi(argv[1]), factorial(atoi(argv[1])));

			}

		else
		{

			printf(" Hijo 2. Pid proceso hijo: %d. Pid proceso padre: %d\n", getpid(), getppid() );

			printf(" Factorial de %d: %ld\n",atoi(argv[2]), factorial(atoi(argv[2])));

		}

		sleep(1);

		exit(EXIT_SUCCESS);

		}

	}

	printf(" Proceso padre: %d\n", getpid() );

	for(int i=0; i<2; i++)
	{

		childpid = wait(&status);

		if(childpid > 0)
		{

			if(WIFEXITED(status)) printf(" Child %d exited, status = %d\n", childpid, WEXITSTATUS(status));

			else if (WIFSIGNALED(status)) printf(" Child %d killed (signal %d)\n", childpid, WTERMSIG(status));
 
			else if (WIFSTOPPED(status)) printf(" Child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));

		}

		else 
		{

		     	   printf(" Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");

	    	    exit(EXIT_FAILURE);

	    	} 

	}

	exit(EXIT_SUCCESS);

}

