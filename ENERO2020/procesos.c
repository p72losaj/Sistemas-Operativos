// EJERCICIO 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char* argv[])
{
	int argumento, i, j, status, factorial = 1;
	pid_t pid, chilpid;
	if(argc!=2)
	{
		printf(" Error de agumentos: ./a.out factorial\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<2; i++)
	{
		pid = fork();
		if(pid == -1) 
		{
			printf(" PROCESO PADRE. No se pueden crear los hijos\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if(i == 0)
			{
				argumento = atoi(argv[1]);
				for(j = 2; j<=argumento; j++) factorial = factorial * argumento;
				printf(" Proceso hijo %d. PID HIJO %d. PID PADRE %d. Valor del factorial %d = %d \n", i+1, getpid(), getppid(), argumento, factorial);
				exit(EXIT_SUCCESS);
			}
			else printf(" Proceso hijo %d. PID HIJO %d. PID PADRE %d. Abriendo la calculadora de gnome\n", i+1, getpid(), getppid());
			execlp("gnome-calculator", "gnome-calculator", (char*) 0);
		}
	}
	// Proceso padre
	while ( (chilpid=waitpid(-1,&status,WUNTRACED | WCONTINUED)) > 0 ) 
	{
		if (WIFEXITED(status)) printf(" Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)chilpid, WEXITSTATUS(status));	
		else if (WIFSIGNALED(status))  printf(" Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)chilpid, WTERMSIG(status));
		else if (WIFSTOPPED(status))  printf(" Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)chilpid,WSTOPSIG(status));
		else if (WIFCONTINUED(status)) printf(" Proceso Padre, Hijo con PID %ld reanudado\n",(long int) chilpid);		  
	}
	if (chilpid==(pid_t)-1 && errno==ECHILD) printf(" Proceso Padre, valor de errno = %d, definido como: %s\n", errno, strerror(errno));
	else
	{
		printf(" Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
		exit(EXIT_FAILURE);
	}	
	exit(EXIT_SUCCESS);
}