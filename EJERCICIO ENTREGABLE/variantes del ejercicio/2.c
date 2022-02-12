/*
	Ejercicio de semaforos 
	Elproductor llena el buffer de datos y el consumidor consume primero las posiciones pares
	y posteriormente las posiciones impares del buffer
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 10
#define ITERACIONES N
sem_t productor;
sem_t consumidor;
sem_t mutex;
int v[N];
int indice=0;
int consumicion=0;
// El productor llena el buffer de datos
void *producir(int *indice)
{
	sem_wait(&productor);
	sem_wait(&mutex);
	for(int i=0;i<N;i++)
	{
		int dato=rand()%10;
		v[i]=dato;
	}
	printf("Buffer de datos lleno... \n");
	if(*indice%2==0) consumicion=0;
	else consumicion=1;
	sem_post(&mutex);
	sem_post(&consumidor);
}
// El consumidor consume los datos producidos por el productor
void *consumir()
{
	sem_wait(&consumidor);
	sem_wait(&mutex);
	if(consumicion==0)
	{
		for(int i=0;i<N;i++)
		{
			if(i%2==0) v[i]=0;
			printf("Consumicion de los datos de las posiciones pares del buffer realizada \n");
		}
		else if(consumicion==1)
		{
			for(int i=0;i<N;i++)
			{
				if(i%2!=0) v[i]=0;
			}
			printf("Consumicion de los datos de las posiciones impares del buffer realizada \n");
		}
	sem_post(&mutex);
	sem_post(&productor);
}

int main()
{
	sem_init(&productor,0,N);
 	sem_init(&consumidor,0,0);
 	sem_init(&mutex,0,1);
 	int numHilos=0;
 	srand(time(NULL));
 	printf("Introduce el numero de hilos: ");
 	scanf("%d",&numHilos);
 	pthread_t tdh[numHilos];
 	int aux[numHilos];
 	for(int i=0;i<numHilos;i++)
	{
		aux[i]=i;
		pthread_create(&tdh[i],NULL,(void *)producir,&aux[i]);
		usleep(10000);
		pthread_create(&tdh[i],NULL,(void *)consumir,NULL);
		usleep(10000);
	}
	for(int i=0;i<numHilos;i++) pthread_join(tdh[i],NULL);
	return 0;
 }