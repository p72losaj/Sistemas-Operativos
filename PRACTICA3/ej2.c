/*

EJERCICIO 2

Tomando como base el ejemplo hilos.c implementar la exclusión mutua usando el algoritmo de la panadería de Lamport.

*/

#include <pthread.h>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <math.h>

#define ITER	100

#define NHILOS	4

#define TRUE 1

#define	FALSE 0

// Solución al problema de la sección crítica para N Hilos

// Algoritmo de Lamport

typedef unsigned char BOOLEAN;

double cont = 0;

BOOLEAN  Elegido[NHILOS];

int ticket[NHILOS]; // un "ticket" por cada hilo

int max (); 

void * Lamport (void * p); // en la funcion Lamport resolvemos el problema de la seccion critica del programa

int main(int argc, char *argv[])
{

	pthread_t hilos[NHILOS];

	int status,i,v[NHILOS];

 	void *adder(void *);

	double *valor;

	for(i=0; i<NHILOS; i++)
	{

		Elegido[i]=FALSE;

		ticket[i]=0;

	}

	for(i=0;i<NHILOS;i++)
	{

		if((status=pthread_create(&hilos[i],NULL,Lamport,(void *) &i))) exit(status);

	}

	for (i=0;i<NHILOS;i++)
	{

		pthread_join(hilos[i], (void **) &valor);

		printf(" El valor devuelto por el hilo %lu es: %.0lf\n", hilos[i], *valor);

	}

	printf(" Valor de la variable contador que nos indica el valor maximo de los hilos: %.0f\n", cont);

	exit(EXIT_SUCCESS);

}

void * Lamport (void * p)
{

	int *num,i,j;

	num = (int *) p;

	double l,*devuelve;

	for (i=0;i<ITER;i++)
	{

		ticket[*num] = max();

		Elegido[*num] = FALSE;

		for (j = 0; j < NHILOS; j++) 
		{

		   	while (Elegido[j]);

		   	while ((ticket[j] != 0) && (ticket[j], j) < (ticket[*num], *num));
		}

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

		cont++;

	// Secci�n residual

		ticket[*num] = 0;

	}

	devuelve = malloc(sizeof(double));

  	*devuelve = cont;

   	pthread_exit((void *) devuelve);

}

int max ()
{

	int max;

	for(int w=0; w<NHILOS; w++)
	{

		if(ticket[w]>max) max=ticket[w];

	}

 	return max;

}
