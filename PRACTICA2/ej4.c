/*

EJERCICIO 4

Crea 2 hebras y cada una incremente en un bucle 50 veces una variable global

Imprime al final del programa principal el valor de la variable 

*/

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

int valor = 0;

void *func(void* argc)
{

	for(int i=0; i<50; i++)	valor++;

	printf(" Saliendo de la hebra\n");

	pthread_exit(NULL);

}

int main( int argc, char *argv[])
{

	pthread_t hebra[2];

	for(int i=0; i<2; i++)
	{
		
		printf( " Creando la hebra %d\n", i+1 );

		if( pthread_create(&hebra[i],NULL, (void*)func, (void*) NULL) )
		{

			printf( " Error crear las hebras\n" );

			exit(EXIT_FAILURE);

		}
		
		if( pthread_join(hebra[i],NULL) )
		{

			printf( "Error al unir las hebras\n" );
			
			exit(EXIT_FAILURE);

		}

	}

	printf( " Valor variable global: %d\n", valor );

	exit(EXIT_SUCCESS);

}