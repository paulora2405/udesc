#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int particiona(int vetor[], int low, int high) {
  int pivot = vetor[high];
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++) {
    if(vetor[j] < pivot) {
      i++;
      swap(&vetor[i], &vetor[j]);
    }
  }
  swap(&vetor[i + 1], &vetor[high]);
  return (i + 1);
}

void quicksort(int vetor[], int low, int high) {
  if(low < high) {
    int pivot = particiona(vetor, low, high);

// #pragma omp task
#pragma omp task final((pivot - low) < omp_get_num_threads()) mergeable default(none) \
    shared(vetor) firstprivate(low, pivot)
    { quicksort(vetor, low, pivot - 1); }
// #pragma omp task
#pragma omp task final((high - pivot) < omp_get_num_threads()) mergeable default(none) \
    shared(vetor) firstprivate(high, pivot)
    { quicksort(vetor, pivot + 1, high); }
  }
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Argumento Necessário: tamanho do vetor!");
    return 1;
  }
  int n = atoi(argv[1]);
  int* vetor = (int*)malloc(sizeof(int) * n);  // Vetor

#if 1
  FILE* filep;
  int index = 0;
  if((filep = fopen("reverse.txt", "r")) == NULL) {
    printf("Failed to open file!\n");
    return 1;
  } else
    while(index < n && (fscanf(filep, "%d", &vetor[index++])) != EOF) {
    }
#else
  srand(time(NULL));
  for(int i = 0; i < n; i++)
    vetor[i] = rand() % n + 1;
#endif

  // Antes do processamento
  double start_time = omp_get_wtime();

#pragma omp parallel
  {
#pragma omp single
    {
      quicksort(vetor, 0, n - 1);  // Ponteiro
    }
  }
  double end_time = omp_get_wtime();
  // Depois do processamento

  printf("%lf\n", end_time - start_time);

  // for(int i = 0; i < n; i++)
  //   printf("%d ", vetor[i]);
  // printf("\n");

  free(vetor);

  return 0;
}