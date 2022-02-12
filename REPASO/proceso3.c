/*

EJEMPLO3: PROCESOS

Realizar un programa que capture la señal de alarma.

Imprimir cadena RING pasados 5 segundos, despues otros 3 y ultimo cada segundo. Este último mediante bucle infinito que imprima el numero de timbres.

Pasados 4 timbres, el proceso se detiene usando kill().

*/

#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>

#include <unistd.h>

#include <errno.h>

#include <sys/wait.h>

#include <signal.h>

// Contamos los segundos

int f1(int seg)
{

	alarm(seg);

	pause();

} // fin_funcion

void sig_alarm(int signo)
{

	printf(" RING.");

	printf(" Valor señal: %d\n", signo);

	return; // retorna para levantar la pausa

} // fin_funcion


int main(int argc, char* argv[])
{

	int timbres=0; 
	
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
	{

		perror(" sig error");
	
		printf(" errno value: %d\n", errno);

		exit(EXIT_FAILURE);

	} // fin_if

	printf(" Alarma en 5 segundos\n");

	// Enviamos las señales

	kill(getpid(), f1(5));
	
	printf(" Alarma en 3 segundos\n");

	kill(getpid(), f1(3));

	while(timbres >= 0)
	{
	
		printf(" Alarma en 1 segundo\n");
	
		kill( getpid(), f1(1) );

		timbres++;

		if( timbres == 5) kill( getpid(), SIGKILL );

	} // fin_while

	exit(EXIT_SUCCESS);

}