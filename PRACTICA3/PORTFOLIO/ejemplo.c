#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 10
#define ITERACIONES N

//productor enchustador donde primero lleno el buffer y luego el hilo consumidor se cepilla primero las posiciones pares y luego las impares

sem_t productor;
sem_t consumidor;
sem_t mutex;

int v[N];
int indice=0;
int consumicion=0;

void *producir(int *indice)
{

	sem_wait(&productor);
	sem_wait(&mutex);

		for(int i=0;i<N;i++)
		{
			int dato=rand()%10;
			v[i]=dato;
		}

		printf("Buffer a full de datos... \n");

		for(int i=0;i<N;i++)
		{
			printf(" %d ",v[i]);
		}

		printf("\n");

		if(*indice%2==0) consumicion=0;

		else consumicion=1;

	sem_post(&mutex);

	sem_post(&consumidor);

}

void *consumir()
{

	sem_wait(&consumidor);
	sem_wait(&mutex);
	
	if(consumicion==0)
		{
	
			printf("Arrebatando los datos de las posiciones pares \n");
			
			for(int i=0;i<N;i++)
				{
					if(i%2==0) v[i]=0;
				
				}

			printf("\n");

			printf("Consumicion par realizada \n");

			for(int i=0;i<N;i++) printf(" %d ",v[i]);

			printf("\n");
		}

		else if(consumicion==1)
		{
			
			printf("Arrebatando los datos de las posiciones impares \n");

			for(int i=0;i<N;i++)
			{
				if(i%2!=0) v[i]=0;

			}

			printf("\n");

			printf("Consumicion impar realizada \n");

			for(int i=0;i<N;i++) printf(" %d ",v[i]);
			
			printf("\n");

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
 	
	printf("Escribe los hilos que quieras que lien la matraca \n ");
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