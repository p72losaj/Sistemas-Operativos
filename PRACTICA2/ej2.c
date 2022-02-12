/*

EJERCICIO2


	Contar lineas de ficheros pasados como parámetros.

	Muestre al final el numero de lineas totales(contando todos los ficheros juntos)

	Crear hilo por fichero, contando en paralelo

*/

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <pthread.h>

void *func(void* fichero)
{

	int *suma = (int*) fichero;

	char nombre[50], buffer[100];

	printf(" Nombre del fichero: ");
	
	scanf("%s", nombre);

	FILE* f;

	if( (f=fopen(nombre,"r+") ) == NULL)
	{
	
		printf(" Error abrir fichero. Errno value: %d",errno);

		exit(EXIT_FAILURE);

	}

	while( fgets(buffer,100,f) != NULL)
		*suma=*suma+1;

	fclose(f);

	pthread_exit(exit);

}


int main(int argc, char* argv[])
{

	pthread_t x;

	if(argc != 2)
	{

		printf(" Error argumentos: ./a.out nficheros\n");

		exit(EXIT_FAILURE);

	}

	int i = 0, suma = 0;

	while( i++ < atoi(argv[1]) )
	{

		if( pthread_create(&x,NULL, (void*) func, (void*) &suma) )
		{

			printf(" Error crear hebras. Errno value: %d\n", errno);

			exit(EXIT_FAILURE);

		}

		if( pthread_join(x, NULL) ) 
		{
	
		  	printf(" Error esperar hebra. Errno value: %d\n", errno);

		  	exit(EXIT_FAILURE);  

		}

	}

	printf(" Suma lineas ficheros: %d\n", suma);

	exit(EXIT_SUCCESS);	

}