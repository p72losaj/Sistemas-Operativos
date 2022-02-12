/*

EJEMPLO1: HEBRAS

Crea N hebras. Cada hebra crea 2 numeros aleatorios flotantes
	
Guarda suma en una variable, devuelta a la hebra llamadora

Hebra principal recoge valores devueltos y suma en variable no global

Utiliza macros definidas y comprobacion de errores(errno y valores devueltos)

*/

#include <unistd.h>

#include <pthread.h>

#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

void* hebra( void* h);

void* hebra2( void* f);

int main(int argc, char* argv[])
{

	if(argc!=3)
	{
		printf(" Error de argumentos: ./a.out nhebras nficheros\n");
		exit(EXIT_FAILURE);
	} // fin_if

	int i, N= atoi(argv[1]), M = atoi(argv[2]);

	float *res;

	int *res2;

	srand48(time(NULL));

	pthread_t *x, *y;

	x = malloc(N*sizeof(pthread_t));

	y = malloc(N*sizeof(pthread_t));

	float suma = 0;

	int suma2 = 0;

	for(i=0; i<N; i++)
	{

		pthread_create(&x[i], NULL, (void*) hebra, (void*) &suma);

		pthread_join(x[i], (void**) &res);

	} // fin_for

	printf(" Suma flotantes = %f\n", *res);

	free(x);

	for(i=0; i<M;i++)
	{

		pthread_create(&y[i], NULL, (void*) hebra2, (void*) &suma2);

		pthread_join(y[i], (void**) &res2);

	} // fin_for

	printf(" Suma lineas de los ficheros = %d\n", *res2);
	
	free(y);

	exit(EXIT_SUCCESS);

} // fin_main

void* hebra( void* h)
{

	float* suma = (float*) h;

	float n1 = drand48() * 10;

	float n2 = drand48() * 10;

	*suma = *suma + (n1+n2);

	printf(" Suma flotantes de la hebra = %f\n", *suma);

	pthread_exit((void*) suma);

} // fin_funcion1

void* hebra2( void* f)
{

	int* suma = (int*) f;

	char nfile[100], buffer[100];

	FILE* f1;

	printf(" Nombre del fichero: ");

	scanf("%s", nfile);

	f1 = fopen(nfile,"r");

	if(f1==NULL)
	{

		printf(" Error abrir fichero\n");

		exit(EXIT_FAILURE);

	} // fin_if

	while(fgets(buffer,100,f1) != NULL) *suma = *suma+1;

	printf(" Suma de lineas del fichero = %d\n", *suma);

	pthread_exit((void*) suma);

} // fin_funcion2