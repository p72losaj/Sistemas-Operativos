/*
Implementar un programa para realizar la suma en forma paralela de los valores de un vector de 10 números enteros que van de 0 a 9 (puede probar con aleatorios). 
Utilice una cantidad de hilos indicada como parámetro de entrada por la linea de argumentos y reparta la suma del vector entre ellos (como considere oportuno). 
La suma debe ser el subtotal devuelto por cada hilo. 
Haga comprobación de errores en su programa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#define TAM 10
struct Dato
{
	int* vector;
	int valor;
};
void* hebra(void* dato)
{
	int i;
	int *suma = malloc(sizeof(int));
	if(suma == 0)
	{
		printf(" Error reservar suma\n");
		exit(EXIT_FAILURE);
	}
	struct Dato dato1=*(struct Dato*)dato;
	if(dato1.valor == 0)
	{
		for(i=0; i<5; i++) *suma = *suma + dato1.vector[i];
	}
	else
	{
		for( i=5; i<10; i++ ) *suma = *suma+dato1.vector[i];
	}
	sleep(2);
	pthread_exit( (void*) suma);
}
int* reservarVector()
{
	int* v = (int*) malloc ( TAM*sizeof(int) );
	if(v == NULL)
	{
		printf(" Error reservar memoria del vector\n");
		exit(EXIT_FAILURE);
	}
	return v;
}
void rellenarVector(int* v)
{
	for(int i=0; i<TAM; i++) v[i] = rand()%10;
}


int main(int argc, char* argv[])
{
	int j, i, x, suma1, suma[2];
	int* cont;
	int sumat=0;
	if(argc!=2)
	{
		printf(" Error argumentos: a.out nhebras\n");
		exit(EXIT_FAILURE);
	}
	x = atoi(argv[1]);
	if(x != 2)
	{
		printf(" Division de vector no disponible\n");
		printf(" Cambiando a 2 hebras\n");
		x = 2;
	}
	srand(time(NULL));
	int* v=reservarVector();
	rellenarVector(v);
	struct Dato dato1;
	dato1.vector = v;
	pthread_t t[x];
	for(j=0; j<x; j++)
	{
		dato1.valor = j;
		if(pthread_create(&t[x], NULL, (void*) hebra, (void*) &dato1) )
		{
			printf(" Error crear hebra. Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(pthread_join(t[x], (void**) &cont) )
		{
			printf("Error unir las hebras \n");
			exit(EXIT_FAILURE);
		}
		suma1 = *(int*) cont;
		suma[j] = suma1;
		printf(" Suma hebra %d: %d\n",j+1,suma[j]);
		sumat= sumat+suma[j];
		sleep(2);
	}
	printf(" Suma de las hebras: %d\n", sumat);
	exit(EXIT_SUCCESS);
}