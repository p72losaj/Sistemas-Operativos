// EJEMPLO 1: SEMAFOROS

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>

#include <time.h>

int par, impar;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[])
{

    if(argc != 2)
    {

        printf(" Error argumentos: ./a.out N\n");

        exit(EXIT_FAILURE);

    } // fin_if

    int N = atoi(argv[1]);

    srandom(time(NULL));

    int pares = 0, impares = 0, *v, *result;

    extern int par, impar;

    extern pthread_mutex_t mutex;

    void* pthread(void*);

    par = impar = 0;

    pthread_t *x;

    x = malloc(N*sizeof(pthread_t));

    v = malloc(N*sizeof(int));

    // Creamos las hebras

    for(int i=0; i<N; i++)
    {

        v[i] = i+1;

        pthread_create(&x[i],NULL,pthread,&v[i]);

    } // fin_for

    // Esperamos finalizacion hebras

    for(int i=0; i<N; i++)
    {

        pthread_join(x[i], (void**) &result);

        printf(" Hebra %d. Valor retornado = %d\n", i+1, *result);

        if( (i+1) %2 == 0) pares+= *result;

        else impares+= *result;

    } // fin_for

    printf(" Valor par %d. Suma pares = %d\n", par, pares );

    printf(" Valor impar %d. Suma impares = %d\n", impar, impares);

    free(x);

    free(v);

} // fin_main

void* pthread(void* id)
{

    extern int par, impar;

    extern pthread_mutex_t mutex;

    int *suma, index;

    index = *(int*) id;

    suma = malloc(sizeof(int)); 

    *suma = 0;

    for(int i=0; i<100; i++)
    {

        int n = random() % 11;

        *suma += n;

        pthread_mutex_lock(&mutex);

        if(index % 2 == 0) par+=n;

        else impar+=n;

        pthread_mutex_unlock(&mutex);

    } // fin_for

    pthread_exit( (void*) suma);

} // fin_funcion