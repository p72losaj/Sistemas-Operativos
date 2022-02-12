// SEMAFOROS NAMED

#include <pthread.h>

#include <stdio.h> 

#include <unistd.h> 

#include <stdlib.h> 

#include <sys/time.h> 

#include <sys/ipc.h> 

#include <sys/shm.h> 

#include <sys/types.h> 

#include <semaphore.h> 

#include <sys/wait.h> 

#include <math.h> 

#include <fcntl.h> 

sem_t *mutex; 

double counter = 0;

#define ITER    10 

#define NHILOS  10


int main(int argc, char *argv[]) 
{    

	pthread_t hilos[NHILOS];    

	int status, i, v[NHILOS],shmid;    

	extern double counter;    

	extern sem_t *mutex;    

	void *adder(void *);    

	double *r_value;    

	key_t key;

	key = ftok("hilos_semaforosnamed.c", 1);    

	if ((shmid = shmget(key, sizeof(double), IPC_CREAT | 0777)) == -1) exit(1);

	mutex = sem_open("sem_example", O_CREAT | O_EXCL, 0644, 1);    

	sem_unlink("sem_example");

    	for (i = 0; i < NHILOS; i++) 
    	{        
		v[i] = i;        

		if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i]))) exit(status);    

	}

	for (i = 0; i < NHILOS; i++) 
	{        

	        pthread_join(hilos[i], (void **) &r_value);        

	        printf(" Value returned by %lu thread: %lf\n", hilos[i], *r_value);    

	}

	printf(" Valor final=%f\n", counter);

	exit(EXIT_SUCCESS);

}

void *adder(void *p) 
{    

	double l, *to_return;    

	extern double counter;    

	extern sem_t *mutex;    

	int *id, i,shmid;    
	
	struct timespec t;    

	key_t key;

	id = (int *) p;    

	key = ftok("hilos_semaforosnamed.c", 1);    

	if ((shmid = shmget(key, sizeof(double), 0)) == -1) perror("Child: ");
    
	for (i = 0; i < ITER; i++) 
    	{    
        
		sem_wait(mutex);        
        
		l = counter;        
        
		printf(" Hilo %d: %f\n", *id, counter);        
        
		l++;        
        
		counter = l;
        
        
		sem_post(mutex);    
    
	}    
    
	to_return = malloc(sizeof(double));
    
	*to_return = counter;
    
	pthread_exit((void *) to_return); 

}
