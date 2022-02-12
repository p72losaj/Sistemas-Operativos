/*

EJEMPLO2: HEBRAS

Guardar producto 2 vectores y matriz*vector

*/

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>

#include <time.h>

#define N 3 // numero de filas

#define M 3 // numero de columnas

struct Dato
{

	int *vector1, *vector2;

	float **matriz;

	int valor;

};

void rellenarVector(int* v);

void rellenarMatriz(float** matriz);

float **reservarMemoria();

void* hebra1(void* d);

void* hebra2(void* d);

void liberarMatriz(float** m);

int main(int argc, char* argv[])
{

	srand(time(NULL));

	srand48(time(NULL));

	int i;

	int *v1, *v2, *res1, *res2;

	float **m;

	int suma1, suma2, s1[N];

	struct Dato* d1;

	pthread_t *x, *y;
	
	v1 = (int*) malloc (N*sizeof(int));

	v2 = (int*) malloc (N*sizeof(int));

	m = reservarMemoria();

	d1 = malloc(sizeof(struct Dato));

	x = malloc(sizeof(pthread_t));

	y = malloc(sizeof(pthread_t));

	printf(" vector1\n");

	rellenarVector(v1);

	printf(" Vector2\n");
	
	rellenarVector(v2);

	printf(" Matriz\n");

	rellenarMatriz(m);

	d1->vector1 = v1;

	d1->vector2 = v2;

	d1->matriz = m;

	for(i=0; i<N; i++)
	{

		d1->valor = i;

		pthread_create(&x[i],NULL, (void*) hebra1, (void*) d1);

		pthread_join(x[i], (void**) &res1);

		suma1 = *(int*) res1;

		pthread_create(&y[i], NULL, (void*) hebra2, (void*) d1);

		pthread_join(y[i], (void**) &res2);

		suma2 = *(int*) res2;

		s1[i] = suma2;

	} // fin_for

	printf(" Suma hebra de vectores = %d\n", suma1);

	printf(" Operaciones matriz\n");

	for(int i=0; i<N; i++)
		printf(" Suma hebra vector 1 %d = %d\n", i+1, s1[i]);

	free(v1);

	free(v2);

	free(d1);

	free(x);

	free(y);

	liberarMatriz(m);

	exit(EXIT_SUCCESS);

} // fin_main

void rellenarVector(int* v)
{

	for(int i=0; i<N; i++)
	{

		v[i] = rand() % 10;

		printf(" %d ", v[i]);

	} // fin_for

	printf("\n");

} // fin_funcion1

void *hebra1(void *d)
{
	
	struct Dato d1 = *(struct Dato*) d;

	int* suma; 

	suma = (int*) malloc (sizeof(int));

	*suma = 0;

	for(int i=0; i<N; i++)
		*suma = *suma + (d1.vector1[i] * d1.vector2[i]);
	
	pthread_exit( (void*) suma);

} // fin_funcion2

void* hebra2(void* d)
{

	struct Dato d1 = *(struct Dato*) d;

	int* suma;

	suma = (int*) malloc (sizeof(int));

	*suma = 0;

	for(int i=0; i<N; i++)
		*suma = *suma + (d1.matriz[d1.valor][i] * d1.vector1[i]);

	printf(" Suma hebra matriz y vector1 = %d\n", *suma);

	pthread_exit( (void*) suma);

} // fin_funcion3

float **reservarMemoria()
{

	float** matriz;

	matriz = (float**) malloc (N*sizeof(float*));

	for(int i=0; i<N; i++)
		matriz[i] = (float*) malloc(N*sizeof(float));

	return matriz;

} // fin_funcion4

void rellenarMatriz(float** matriz)
{

	for(int i=0; i<N;i++)
	{

		for(int j=0; j<M; j++)
		{

			matriz[i][j] = drand48() * 11;

			printf(" %f ", matriz[i][j]);

		} // fin_for
	
	} // fin_for

	printf("\n");

} // fin_funcion5

void liberarMatriz(float** m)
{

	for(int i=0; i<N; i++)
		free(m[i]);

	free(m);

} // fin_funcion6