/*

EJERCICIO1

Crea N hebras.	Cada hebra crea 2 numeros aleatorios flotantes

Guarda suma en una variable, devuelta a la hebra llamadora

Hebra principal recoge valores devueltos y suma en variable no global

Utiliza macros definidas y comprobacion de errores(errno y valores devueltos)

*/

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <errno.h>

#include <time.h>

#define M 20

#define L 10

void* func( void *h)
{

	float *suma =(float*) h;

	float numero2 = drand48()*(M-L)+L;

	float numero1 = drand48()*(M-L)+L;

	*suma = *suma +(numero1+numero2);

	printf(" Suma hebra: %f\n", (numero1+numero2));

	pthread_exit(NULL);

} 


int main(int argc, char* argv[])
{

	srand48(time(NULL));

	pthread_t x;

	int N;

	float suma=0;

	printf(" Numero de hebras: ");
	
	scanf(" %d",&N);
	
	for(int i=0; i<N; i++)
	{

		if(pthread_create(&x,NULL, (void*) func, (void*) &suma))
		{

			printf("Error crear hebra. Errno value: %d",errno);

			exit(EXIT_FAILURE);

		} 

		printf(" Creando hebra %d\n", i+1);

		if( pthread_join(x, NULL) ) 
		{

		  	printf("Error esperar hebra. Errno value: %d\n", errno);

		  	exit(EXIT_FAILURE);  

		} 

		printf(" Hebra %d finalizada\n", i+1);

	}

	printf(" Suma final: %f\n",suma);

	exit(EXIT_SUCCESS);

}