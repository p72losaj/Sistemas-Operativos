/*
	Ejercicio de semaforos
	El consumidor espera a que el buffer este lleno y empieza a consumir por el final 
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define N 10
int v[N];
int indice=0;
sem_t productor;
sem_t consumidor;
sem_t mutex;
// El productor introduce los datos en el buffer
void *producir()
{
	sem_wait(&productor);
	sem_wait(&mutex);
	for(int i=0;i<N;i++)
	{
		int dato=rand()%10;
		v[i]=dato;	
	}
	printf("Se ha rellenado de datos el buffer\n");
	sem_post(&mutex);
	sem_post(&consumidor);
}
// El consumidor consume los datos del buffer
void *consumir()
{
	sem_wait(&consumidor);
	sem_wait(&mutex);
	for(int i=N;i>0;i--) v[i-1]=0;
	printf("Datos del buffer consumidos\n");
	sem_post(&mutex);
	sem_post(&productor);
}
int main()
{
	srand(time(NULL));
	int numHilos=0;
	sem_init(&productor,0,N);
	sem_init(&consumidor,0,0);
	sem_init(&mutex,0,1);
	printf("Introduce el numero de hilos: ");
	scanf("%d",&numHilos);
	pthread_t tdhP[numHilos];
	pthread_t tdhC[numHilos];
	for(int i=0;i<numHilos;i++)
	{
		pthread_create(&tdhP[i],NULL, (void *)producir,NULL);
		usleep(10000);
		pthread_create(&tdhC[i],NULL, (void *)consumir,NULL);
		usleep(10000);
	}
	for(int i=0;i<numHilos;i++)
	{
		pthread_join(tdhP[i],NULL);
		pthread_join(tdhC[i],NULL);
	}
return 0;
}