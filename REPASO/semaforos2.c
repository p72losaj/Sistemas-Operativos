// EJEMPLO2: SEMAFOROS

#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer[100];

void* Producir();

void* Consumir(void*);


int main(int argc, char*argv[])
{

	if(argc!=3)
	{

		printf(" Error argumentos: ./a.out Nhebras 0:par;1:impar\n");

		exit(EXIT_FAILURE);

	} // fin_if

	srandom(time(NULL)); // Inicializa semilla aleatoria

	int N = atoi(argv[1]);

	int opcion = atoi(argv[2]);

	extern pthread_mutex_t mutex;

	pthread_t *x, *y;

	x=malloc(N*sizeof(pthread_t));

	y=malloc(N*sizeof(pthread_t));

	// Creamos las N hebras de produccion

	for(int i=0; i<N; i++) pthread_create(&x[i], NULL, (void*) Producir, NULL);

	// Unimos las N hebras de produccion

	for(int i=0; i<N; i++) pthread_join(x[i], NULL);

	// Creamos las N hebras de consumicion

	for(int i=0; i<N; i++) pthread_create(&y[i], NULL, (void*) Consumir, (void*) &opcion);

	// Unimos las hebras

	for(int i=0; i<N; i++) pthread_join(y[i], NULL);

	printf(" Mostrando el buffer\n");

	for(int i=0; i<N; i++) printf("%d ", buffer[i]);

	printf("\n");

	free(x);

	free(y);

	exit(EXIT_SUCCESS);

} // fin_main

void* Producir()
{

	extern pthread_mutex_t mutex;

	for(int i=0; i<100; i++)
	{

		int n = random() % 11+1;

		pthread_mutex_unlock(&mutex);

		buffer[i] = n;

		pthread_mutex_lock(&mutex);

	} // fin_for

	pthread_exit(NULL);

} // fin_Producir

void* Consumir(void* id)
{

	extern pthread_mutex_t mutex;

	int opcion = *(int*) id;

	for(int i=0; i<100; i++)
	{

		pthread_mutex_unlock(&mutex);

		if(opcion==0 && i%2==0) buffer[i] = 0;

		if(opcion==1 && i%2 !=0) buffer[i] = 0;

		pthread_mutex_lock(&mutex);

	} // fin_for

	pthread_exit(NULL);

} // fin_Consumir