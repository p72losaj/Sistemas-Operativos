/*

EJEMPLO2: PROCESOS

El hijo debe imprimir un mensaje en pantalla cada vez que recibe la señal del padre, tratándola en una función aparte llamada tratarSennal(). 

Enviados 5 mensajes los procesos deben salir. Utiliza las funciones signal() y kill().

*/

#include <sys/types.h>

#include <sys/wait.h>

#include <signal.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <string.h>

void tratarSennal(int n);

int main( int argc, char* argv[] )
{

	pid_t pid, chilpid;

	int status;

	int contador = 0;

	pid = fork();

	// Caso error

	if( pid == -1 )
	{

		printf(" fork error\n");

		printf(" errno value: %d\n",errno);

		exit(EXIT_FAILURE);

	} // fin_if

	// Caso hijo

	if( pid == 0 )
	{

		printf(" Proceso hijo: %d; padre: %d\n", getpid(), getppid() );

		signal(SIGUSR1, tratarSennal);

		while(1);

		pause(); 

	} // fin_if

	// Proceso padre
	
	if( pid > 0)
	{

		while(1)
		{

			sleep(1);

			if( contador == 5 )
			{
				kill(pid, SIGKILL);
				
				//Esperamos a que termine el hijo

				chilpid = waitpid(-1,&status, WUNTRACED|WCONTINUED);

				if(chilpid > 0)
				{

					if( WIFEXITED(status) )
						printf( " Proceso padre. Hijo con PID %ld finalizado, status = %d\n", (long int)chilpid, WEXITSTATUS(status) );

					if( WIFSIGNALED(status) )	
						printf( " Proceso padre. Hijo con PID %ld eliminado, status = %d\n", (long int)chilpid, WTERMSIG(status) );

					if(WIFSTOPPED(status) )
						printf( " Proceso padre. Hijo con PID %ld detenido, status = %d\n", (long int) chilpid, WSTOPSIG(status) );
				
				} // fin_if

				if( (chilpid == (pid_t)-1 ) && errno == ECHILD )
					printf( " PROCESO PADRE. Valor de errno %d definido como = %s\n", errno, strerror(errno) );
				
				exit(EXIT_SUCCESS);
			} // fin_if

			kill(pid, SIGUSR1);

			contador++;

		} // fin_while

	} // fin_if

	exit(EXIT_SUCCESS);

} // fin_main

void tratarSennal(int n)
{

	printf(" Recibida señal de padre: %d \n", n);

} // fin_funcion