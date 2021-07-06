/*
 *  Calcula produto escalar (dot product) de 2 vetores.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000.0 + t.tv_usec;
}

/*
 * Inicializa vetores
 */
void init_vectors(double *a, double *b, int n) {
  int i;
  for(i = 0; i < n; i++) {
    a[i] = 0.5;
    b[i] = 1.0;
  }
}

/*
 * Calcula o produto escalar (varias vezes)
 */
double dot_product(double *a, double *b, int n, int repeat) {
  double dot;
  int k, i;
  for(k = 0; k < repeat; k++) {
    dot = 0.0;
    for(i = 0; i < n; i++) {
      dot += a[i] * b[i];
    }
  }
  return dot;
}

int main(int argc, char **argv) {
  int n;
  int repeat;
  double dot;
  long start_time, end_time;

  if((argc != 3)) {
    printf("Uso: %s <tamanho dos vetores> <repeticoes>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);       // tamanho dos vetores
  repeat = atoi(argv[2]);  // numero de repeticoes (variar carga)

  // Cria vetores (sem testar erro de alocacao)
  double *a = (double *)malloc(sizeof(double) * n);
  double *b = (double *)malloc(sizeof(double) * n);

  init_vectors(a, b, n);

  start_time = wtime();
  dot = dot_product(a, b, n, repeat);
  end_time = wtime();

  printf("Produto escalar = %f\n", dot);
  printf("Tempo de calculo = %ld usec\n", (long)(end_time - start_time));

  free((void *)a);
  free((void *)b);

  return 0;
}
