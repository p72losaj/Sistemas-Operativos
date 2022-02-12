// SEMAFORO UNNAMED

#include <pthread.h> 

#include <stdio.h> 

#include <unistd.h> 

#include <stdlib.h> 

#include <sys/time.h> 

#include <string.h> 

#include <semaphore.h> 

#include <sys/ipc.h> 

#include <sys/shm.h> 

#include <sys/types.h>

double counter = 0; 

sem_t *mutex; 

#define ITER    10 

#define NHILOS  10

int main(int argc, char*argv[]) 
{    

	pthread_t hilos[NHILOS];    

	int status, i, v[NHILOS],shmid;    

	extern double counter;    

	void *adder(void *);    

	double *r_value;    

	key_t key;    

	extern sem_t *mutex;    

	key=ftok("hilos_semaforosunnamed.c",1);   

	if((shmid=shmget(key,sizeof(double),IPC_CREAT | 0777))==-1) exit(1);

    	key = ftok("hilos_semaforosunnamed.c", 2);    
    
	if ((shmid = shmget(key, sizeof(double), IPC_CREAT | 0777)) == -1) exit(1);  
    
	mutex = (sem_t *) shmat(shmid, NULL, 0);    
    
	sem_init(mutex, 1, 1);

    
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

	key_t key;    

	struct timespec t;    

	key = ftok("unnamed_sem_t_ok.c", 1);    

	if ((shmid = shmget(key, sizeof(double), 0)) == -1) perror("Child: ");
    
	id = (int *) p;    
    
	sem_wait(mutex);    
    
	for (i = 0; i < ITER; i++) 
    
	{            
    		
		l = counter;        

	    	printf(" Hilo %d: %f\n", *id, counter);        
    	
		l++;        

	    	counter = l;

	}    

	sem_post(mutex);

	to_return = malloc(sizeof(double));
    
	*to_return = counter;
    
	pthread_exit((void *) to_return); 

}
