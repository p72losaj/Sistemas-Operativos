/*
	Ejemplo de semaforos donde un productor produce datos y un consumidor los consume conforme el productor los produce
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 10
#define hilos N
int indice=0;
int v[N];
sem_t productor;
sem_t consumidor;
sem_t mutex;
// Productor produce los datos
void *producir(int *i)
{
	int dato=rand()%10;
	sem_wait(&productor);
	sem_wait(&mutex);
	v[indice]=dato;
	indice++;
	printf("Buffer de datos lleno\n");
	sem_post(&mutex);
	sem_post(&consumidor);
	pthread_exit(NULL);
}
// El consumidor consume los datos producidos por el productor
void *consumir(int *i)
{
	sem_wait(&consumidor);
	sem_wait(&mutex);
	v[indice-1]=0;
	printf("Consumidor consume los datos del buffer\n");
	sem_post(&mutex);
	sem_post(&productor);
}

int main()
{
	sem_init(&mutex,0,1);
	sem_init(&productor,0,N);
	sem_init(&consumidor,0,0);
	srand(time(NULL));
	pthread_t tdh[2];
	for(int i=0;i<hilos;i++)
	{
		pthread_create(&tdh[i],NULL,(void *)producir,&i);
		usleep(10000);
		pthread_create(&tdh[i],NULL,(void *)consumir,&i);
		usleep(10000);
	}
	for(int i=0;i<hilos;i++) pthread_join(tdh[i],NULL);
}