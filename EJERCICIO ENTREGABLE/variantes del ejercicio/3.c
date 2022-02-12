/*
	Ejercicio de semaforos
	El consumidor consume posiciones aleatorias despues de que el productor introduzca los datos en el buffer
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define N 10
int v[N];
int acceso=N;
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
	printf("Datos introducidos en el buffer \n");
	sem_post(&mutex);
	sem_post(&consumidor);
	pthread_exit(NULL);
}
// El consumidor consume los datos del buffer
void *consumir()
{
	sem_wait(&consumidor);
	sem_wait(&mutex);
	for(int j=0;j<N;j++)
	{
		int pos=rand()%10;
		for(int i=0;i<N;i++)
		{
			if(i==pos)
			{
				v[i]=0;
				printf("Se ha consumido el dato en la posicion aleatoria %d del buffer \n", i);
				}
			}
	}
	sem_post(&mutex);
	sem_post(&productor);
}

int main()
{
	srand(time(NULL));
	sem_init(&productor,0, N);
	sem_init(&consumidor,0,0);
	sem_init(&mutex,0,1);
	int numHilos=0;
	printf("Introduce el numero de hilos: ");
	scanf("%d", &numHilos);
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