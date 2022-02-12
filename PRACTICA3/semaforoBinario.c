// SEMAFORO BINARIO

#include <pthread.h> 

#include <stdio.h> 

#include <unistd.h> 

#include <stdlib.h> 

#include <sys/time.h> 

#include <string.h> 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double counter = 0;

#define ITER 10

#define NHILOS 10

int main(int argc, char *argv[])
{

	pthread_t hilos[NHILOS];

	int status, i, v[NHILOS];

	extern double counter;

	void * add(void*);

	double *valor;

	for(i=0; i<NHILOS; i++)
	{

		v[i] = i;

		if((status=pthread_create(&hilos[i], NULL,add,(void*)&v[i]) ) ) exit(status);

	}

	for(i=0; i<NHILOS; i++)
	{

		pthread_join(hilos[i], (void**) &valor );

		printf(" Value returned by %lu thread: %lf\n", hilos[i], *valor); 

	}

	printf(" Value final=%f\n", counter); 

	exit(EXIT_SUCCESS);

}

void *add(void *p)
{  

	double l, *to_return;    

 	extern double counter;

 	extern pthread_mutex_t mutex;

 	int *id, i;    

 	struct timespec t;

	id = (int *) p;    

	pthread_mutex_lock(&mutex);    

	for (i = 0; i < ITER; i++) 
	{  
    		
		l = counter;

	    	printf(" Hilo %d: %f\n", *id, counter);        

	    	l++;        

	    	counter = l;  

	}    

	pthread_mutex_unlock(&mutex);

	to_return = malloc(sizeof(double));

	*to_return = counter;

	pthread_exit((void *) to_return); 

}

