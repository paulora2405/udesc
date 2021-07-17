#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);

void mergesort(int *v, int n) {
  int *c = malloc(sizeof(int) * n);
#pragma omp parallel
  {
#pragma omp single
    { sort(v, c, 0, n - 1); }
  }
  free(c);
}

void sort(int *v, int *c, int i, int f) {
  if(i >= f)
    return;

  int m = (i + f) / 2;

#pragma omp task
  { sort(v, c, i, m); }
#pragma omp task
  { sort(v, c, m + 1, f); }

  if(v[m] <= v[m + 1])
    return;

  merge(v, c, i, m, f);
}

void merge(int *v, int *c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for(z = i; z <= f; z++)
    c[z] = v[z];

  z = i;
  while(iv <= m && ic <= f) {
    if(c[iv] <= c[ic])
      v[z++] = c[iv++];
    else
      v[z++] = c[ic++];
  }
  while(iv <= m)
    v[z++] = c[iv++];
  while(ic <= f)
    v[z++] = c[ic++];
}

int main(int argc, char const *argv[]) {
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

  double start_time = omp_get_wtime();

  mergesort(vetor, n);  // Ponteiro

  double end_time = omp_get_wtime();

  printf("%lf\n", end_time - start_time);

#if 0
  for(int i = 0; i < n; i++)
    printf("%d ", vetor[i]);
  printf("\n");
#endif

  free(vetor);

  return 0;
}
