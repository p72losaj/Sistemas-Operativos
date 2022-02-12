/*

EJERCICIO 7

El hijo debe imprimir un mensaje en pantalla cada vez que recibe la señal del padre, tratándola en una función aparte llamada tratarSennal(). 

Enviados 5 mensajes los procesos deben salir. Utiliza las funciones signal() y kill().

Crea un proceso hijo y le envia una señal cada segundo de usuario SIGUSR1

*/

#include <sys/types.h>

#include <sys/wait.h>

#include <signal.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

void tratarSennal(int n);


int main( int argc, char *argv[])
{

	pid_t pid, pid_aux;

	int status;

	int m = 0;

	pid = fork();

	if(pid == -1)
	{

		printf("fork error\n");

		printf(" Errno value: %d\n",errno);

		exit(EXIT_FAILURE);

	}

	/*
	Pone tratarSennal() para tratar la señal SIGUSR1
	La mete en un bucle de espera
	*/	

	if(pid == 0)
	{

		printf(" Proceso hijo: %d; padre: %d\n", getpid(), getppid() );

		signal(SIGUSR1, tratarSennal);

		while(1);

		pause();

	}

	// Proceso padre. Cada segundo envia una señal SIGUSR1 a su proceso hijo. Sale al enviar 5 mensajes.

	if(pid > 0)
	{

		while(1)
		{

			sleep(1);

			if(m==5)
			{

				kill(pid, SIGKILL);

				printf(" Señal eliminada\n");

				pid_aux = wait(&status);

				if(pid_aux > 0)
				{

					if(WIFEXITED(status)) printf("Hijo <%d> exited. Pid <%d>\n", pid_aux, WEXITSTATUS(status));
					
					if(WIFSIGNALED(status)) printf("Hijo <%d> killed. Pid <%d>\n", pid_aux, WTERMSIG(status));
					
					if(WIFSTOPPED(status)) printf("Hijo <%d> stopped. Pid <%d>\n", pid_aux, WSTOPSIG(status));
					
				}

				exit(EXIT_SUCCESS);

			}

			kill(pid, SIGUSR1);

			m++;

		}

	}



}

/*
	FUNCION TRATAMIENTO SEÑAL
	ESCRIBE POR PANTALLA UN AVISO DE LLEGADA DE SEÑAL
*/

void tratarSennal(int n)
{
	printf("Recibida señal de padre: %d \n", n);
}