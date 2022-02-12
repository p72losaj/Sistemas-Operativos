/*

EJERCICIO 3

Implemente un programa donde se creen dos hijos. Uno de ellos que abra la calculadora de su distribución de Linux.

El otro que abra un editor de textos con N ficheros pasados como argumentos

*/

#include <stdio.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <sys/types.h>

#include <errno.h>

#include <unistd.h>

void crear_ficheros(char* f1,char** f2);

void abrircalculadora(char* f1, char** f2);

int main(int argc, char* argv[])
{

	int nFicheros; 

	printf(" Numero de ficheros: ");

	scanf("%d",&nFicheros);

	if(argc != 3+nFicheros)
	{

		printf(" Error argumentos: ej3 bc nano nficheros.txt\n");

		exit(EXIT_FAILURE);

	}

	pid_t pid, chilpid;

	int status;

	for(int i=0 ; i<2; i++)
	{

		pid = fork();

		switch(pid)
		{
			case -1: //caso error
				perror("fork error");
				printf(" errno value = %d\n", errno);
				exit(EXIT_FAILURE);

			case 0: //hijo

				if(i == 0)
				{
	
					printf(" Soy el hijo %d. Proceso : %d. Mi padre = %d\n", i+1, getpid(), getppid() );

					abrircalculadora(argv[1], &argv[2]);

				}

				else
				{

					printf(" Soy el hijo %d. Proceso: %d. Mi padre = %d\n",i+1,getpid(), getppid() );

					crear_ficheros(argv[2], &argv[2]);

				}

				exit(EXIT_SUCCESS);

		}

	}

	printf(" Proceso padre %d; mi padre %d\n", getpid(), getppid() );

	for(int i=0 ; i<2; i++)
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

void crear_ficheros(char* f1,char** f2)
{

	if (execvp(f1, f2) < 0 ) //Exec devuelve -1 en caso de error 
	{

		perror("exec");

		printf(" Errno value= %d\n", errno); 

		exit(EXIT_FAILURE);

	}

}

void abrircalculadora(char* f1, char** f2)
{
	
	if (execvp(f1, f2) < 0) //Exec devuelve -1 en caso de error 
	{
		perror("exec");

		printf(" Errno value= %d\n", errno); 

		exit(EXIT_FAILURE);

	}
	
}