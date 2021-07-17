#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

static void dump_list(const char *tag, int *ptr, int left, int right) {
  printf("%15s [%d..%d]: ", tag, left, right);
  for(int i = left; i <= right; i++)
    printf(" %3d", ptr[i]);
  putchar('\n');
}

// Partitioning algorithm
static int partition(int *L, int left, int right) {
  int pivot = left;
  int p_val = L[pivot];

  while(left < right) {
    while(L[left] <= p_val)
      left++;
    while(L[right] > p_val)
      right--;
    if(left < right)
      swap(&L[left], &L[right]);
  }
  swap(&L[pivot], &L[right]);
  return right;
}

// Quicksort recursion
static void quicksort(int *L, int start, int end) {
  if(start >= end)
    return;
  // dump_list("PRE-PARTITION", L, start, end);
  int splitPoint = partition(L, start, end);
  // dump_list("POST-PARTITION", L, start, end);
  // printf("Split point: %d\n", splitPoint);
  quicksort(L, start, splitPoint - 1);
  quicksort(L, splitPoint + 1, end);
}

int main(int argc, char **argv) {
  if(argc != 2) {
    printf("Argumento Necessário: tamanho do vetor!");
    return 1;
  }
  int n = atoi(argv[1]);
  int *vetor = (int *)malloc(sizeof(int) * n);  // Vetor

#if 1
  FILE *filep;
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

  // #pragma omp parallel
  {
    // #pragma omp single
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