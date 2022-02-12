// Semaforo contador

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include<unistd.h>


pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;//INICIALIZA EL SEMAFORO
#define N 100
#define C 100
#define P 1
int buffer[N];
void* producir();
void* consumir();

int main(int argc, char const *argv[]) 
{
	for(int i=0; i<N; i++)
	{
	    buffer[i]=0;
	    if(buffer[i]!=0)
		printf("ERROR al limpiar el buffer");
  	}

	srand(time(NULL));
	
	pthread_t productor[P], consumidor[C];
	
	for(int w=0; w<P; w++)
	{
    		if(pthread_create(&productor[w], NULL, (void*)producir, NULL))
		{
			printf("Error al crear el hilo\n");
			exit(EXIT_FAILURE);
    		}
  	}

  	for(int w=0; w<C; w++)
	{
    		if(pthread_create(&consumidor[w], NULL, (void*)consumir, NULL))
		{
		    printf("Error al crear el hilo\n");
		    exit(EXIT_FAILURE);
    		}
  	}

	int *suma_productor=(int*)malloc(sizeof(int));
	int *suma_consumidor=(int*)malloc(sizeof(int));

	for(int w=0; w<P; w++)
	{
    		if(pthread_join(productor[w], (void **) &suma_productor))
		{
     			printf("Error al parar el hilo\n");
			exit(EXIT_FAILURE);
    		}
  	}

  printf("Suma productores es: %d\n", *suma_productor);
  printf("Consumiendo buffer\n");

  for(int w=0; w<C; w++)
	{
    		if(pthread_join(consumidor[w], (void **) &suma_consumidor))
		{
		    printf("Error al parar el hilo\n");
		    exit(EXIT_FAILURE);
    		}
		
		printf("%d\t",buffer[w]);
  	}

  printf("\nSuma consumidores es: %d\n",*suma_consumidor);

  free(suma_productor);

  free(suma_consumidor);

  pthread_mutex_destroy(&semaforo);

  return 0;
}


void *producir(){

  int *suma=0;
  if( ( suma = (int*)malloc(N * sizeof(int)) ) == NULL)
  {
    printf("\nERROR: No se pudo reservar memoria. Saliendo...\n");
    exit(-1);
  }
  pthread_mutex_lock(&semaforo);
  printf("Llenando buffer\n");
  for(int i=0; i<N; i++){
     buffer[i]=rand()%1000;
     printf("%d\t",buffer[i] );
    *suma+=buffer[i];
  }
  printf("\n");
  pthread_mutex_unlock(&semaforo);
  pthread_exit((void *)suma);
}

void *consumir(){

  int *suma=(int*)malloc(sizeof(int));
  int i;
  *suma=0;
  pthread_mutex_lock(&semaforo);
  for(int i=0; i<N; i++){
    *suma+=buffer[i];
  }
  pthread_mutex_unlock(&semaforo);
  pthread_exit((void *)suma);
}
