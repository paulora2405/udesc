#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

typedef struct{
	int id;
	int qnt;
}list_st;

typedef struct{
	int m;
	int n;
	int *linhaptr;
	list_st *list;
}arg_st;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier1, barrier2;

void *thread_impares(void *arg){
	

	arg_st *args = (arg_st *)arg;
	int *a = args->linhaptr;
	int n = args->n;
	list_st *l = args->list;
	int m = args->m;

	pthread_barrier_wait(&barrier1);
	int impares = 0;

	for(int i=0; i<n; i++){
		if(a[i]%2 != 0)
			impares++;
	}
	
	pthread_mutex_lock(&mtx); //comeca regiao critica
	int i = 0;
	while(l[i].id != -1)
		i++;
	l[i].id = m;
	l[i].qnt = impares;
	pthread_mutex_unlock(&mtx); //termina regiao critica
	

	pthread_barrier_wait(&barrier2);

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int m = 0, n = 0, rc;
    m = atoi(argv[1]); //argv[0] eh o nome do programa
    n = atoi(argv[2]);

	if(m == 0|| n == 0){
		perror("erro no tamanho da matriz");
		exit(1);
	}
	

	rc = pthread_barrier_init(&barrier1, NULL, m);
    if (rc != 0) {
		perror("erro no pthread_barrier_init() n1");
		exit(1);
    }
	rc = pthread_barrier_init(&barrier2, NULL, m);
    if (rc != 0) {
		perror("erro no pthread_barrier_init() n2");
		exit(1);
    }
	pthread_t threads[m];

    int **matriz;
	matriz = malloc(m * sizeof(int*));
    for(int i=0; i<m; i++){
		matriz[i] = malloc(sizeof(int)*n);
   	}
	
	srand(time(NULL));
	for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
        	matriz[i][j] = rand();
    	}
   	}
	
	arg_st args[m];
	list_st *list;
	list = malloc(m * sizeof(list_st));
	for(int i=0; i<m; i++)
		list[i].id = -1;

	for(int i=0; i<m; i++){
		args[i].n = n;
		args[i].list = list;
		args[i].m = i;
		args[i].linhaptr = matriz[i];
		rc = pthread_create(&(threads[i]), NULL, thread_impares, (void *)&args[i]);
		if(rc){
			perror("erro no pthread_create");
			exit(1);
		}
	}

	for(int i=0; i<m; i++){
		rc = pthread_join(threads[i], NULL);
		if (rc != 0) { 
			perror("erro no pthread_join");
			exit(1);
		}
	}

	for(int i=0; i<m; i++){
		printf("Thread %d tem %d numeros impares\n", list[i].id, list[i].qnt);
	}

	rc = pthread_barrier_destroy(&barrier1);
	if (rc != 0) {
		perror("erro no pthread_barrier_destroy() n1");
		exit(1);
    }
	
	rc = pthread_barrier_destroy(&barrier2);
	if (rc != 0) {
		perror("erro no pthread_barrier_destroy() n2");
		exit(1);
    }
	

	for(int i=0; i<m; i++)
		free(matriz[i]);
	free(matriz);
	free(list);
}