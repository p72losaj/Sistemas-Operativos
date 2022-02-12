/*

EJERCICIO 1: b

Crear N sucesos: 1->2->3->...->N

*/

#include <sys/types.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <sys/wait.h>

int main( int argc, char* argv[])
{

	pid_t pid, childpid;

	int status ,N, i;

	printf(" Numero de hijos: ");

	scanf("%d",&N);

	for( i = 1 ; i < N; i++)
	{

		pid = fork();

		if(pid == -1)
		{

			printf(" Error de fork. Valor de error: %d\n", errno);

			exit(EXIT_FAILURE);

		}

		else if(pid == 0) printf(" Hijo <%d>. Pid del padre: <%d>\n", getpid(), getppid() );

		else
		{

			printf(" Padre <%d>. Pid del padre <%d>\n", getpid(), getppid() );

			childpid = wait(&status);

			if(childpid > 0)
			{

				if(WIFEXITED(status)) printf("child %d exited, status = %d\n", childpid, WEXITSTATUS(status));

				else if (WIFSIGNALED(status)) printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));

				else if (WIFSTOPPED(status)) printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
        		
        			else 
				{     	   		

					printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			
			    	    	exit(EXIT_FAILURE);
	    			}

			}

		}

	}

	exit(EXIT_SUCCESS);

}