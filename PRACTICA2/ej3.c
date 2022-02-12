
/*

EJERCICIO 3

Multiplicacion en paralelo de una matriz 3x3 por un vector 3x1.
Crea 3 hebras que se repartan las filas de la matriz y el vector.
Cada hijo imprime la fila que le tocó y el resultado final del producto, que envía al padre.
El padre espera la terminación de cada hijo y muestra el vector resultante.

*/

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <time.h>

#define fil 3

#define col 3

struct Dato
{

	int* vector;

	float **Matriz;

	int valor;

};

int *reservarVector()
{

	int *v;

	v=(int*)malloc(fil*sizeof(int));

	if( v == NULL )
	{

		printf(" Error reservar memoria del vector.\n");

		exit(EXIT_FAILURE);

	}

	return v;

}

float **reservarMatriz()
{

	float** matriz;

	matriz = malloc(fil*sizeof(int));

	if( matriz == NULL )
	{

		printf(" Error reservar filas matriz\n");

		exit(EXIT_FAILURE);	

	}

	for(int i=0; i<col; i++)
	{

		matriz[i] = malloc(col*sizeof(int));

		if( matriz[i] == NULL )
		{
		
			printf("Error reservar columna matriz\n");
		
			exit(EXIT_FAILURE);

		}

	}

	return matriz;

}

void rellenarVector(int* v)
{

	for(int i=0; i<fil; i++)
	{

		v[i] = rand()%10;

		printf(" V[%d]=%d\n", i, v[i]);

	}

}

void rellenarMatriz(float **matriz)
{

	int i,j;

	for(i=0; i<fil;i++)
	{

		for(j=0;j<col;j++)
		{

			matriz[i][j] = drand48()*20;

			printf(" Matriz [%d][%d]= %f\n",i,j,matriz[i][j]);

		}

	}

}

void* hebra(void* dato)
{

	float *suma=malloc(sizeof(float));

	if( suma == NULL )
	{

		printf(" Error reservar memoria suma\n");

		exit(EXIT_FAILURE);

	}

	*suma = 0;

	struct Dato dato1=*(struct Dato*)dato;

	for(int j=0; j<fil;j++) *suma = *suma+(dato1.Matriz[dato1.valor][j]*dato1.vector[j]);
	
	pthread_exit( (void*) suma);

}

int main( int argc, char* argv[] )
{
	int i, j, suma1, suma[3];

	int *ret;

	int *v = reservarVector();

	float **Matriz = reservarMatriz();

	srand( time(NULL) );

	rellenarVector(v);

	srand48( time(NULL) );

	rellenarMatriz(Matriz);

	struct Dato *dato1 = malloc( sizeof(struct Dato) );

	if( dato1 == NULL )
	{

		printf("Error reservar memoria del struct\n");

		exit(EXIT_FAILURE);

	}

	dato1->vector = v;

	dato1->Matriz = Matriz;

	pthread_t x[3];

	for(i=0; i<fil; i++)
	{

		dato1->valor = i;

		if( pthread_create(&x[i], NULL,(void*) hebra, (void*) dato1) )
		{

			printf(" Error crear hebra\n");

			exit(EXIT_FAILURE);

		}

		if(pthread_join(x[i], (void**) &ret))
		{

			printf("Error unir las hebras\n");

			exit(EXIT_FAILURE);

		}

		suma1 = *(int*)ret;

		suma[i] = suma1;

	}

	for(int i=0; i<3; i++) printf(" Hebra %d.Suma fila %d : %d\n",i+1,i, suma[i]);
	
	exit(EXIT_SUCCESS);

}