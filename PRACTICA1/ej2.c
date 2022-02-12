
// EJERCICIO 2

#include <sys/types.h>

#include <sys/wait.h>

#include <stdlib.h>

#include <stdio.h>

#include <errno.h>

#include <unistd.h>

int main( int argc, char *argv[])
{

	pid_t pid, childpid;

	int status;

	pid =fork();

	switch(pid)
	{

		//Caso de error

		case -1:

			perror("fork error");

			printf(" Errno value=%d\n",errno);

			exit(EXIT_FAILURE);

		//Caso del hijo

		case 0:
			printf(" Soy el hijo %d. Padre %d\n",getpid(), getppid());

			exit(EXIT_SUCCESS);

		//Caso del padre

		default:

			sleep(2);

			printf(" Soy el padre %d; padre %d\n", getpid(),getppid());

			exit(EXIT_SUCCESS);

	}



}