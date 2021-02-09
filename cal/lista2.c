#include <stdio.h>
#include <stdlib.h>

void printVet(int *a, int n);

int esquerda(int i) { return (2 * i + 1); }

int direita(int i) { return (2 * i + 2); }

void heapify(int *a, int n, int i) {
  printVet(a, n);
  int e, d, maior, aux;
  e = esquerda(i);
  d = direita(i);
  if(e < n && a[e] > a[i])
    maior = e;
  else
    maior = i;
  if(d < n && a[d] > a[maior]) maior = d;
  if(maior != i) {
    aux = a[i];
    a[i] = a[maior];
    a[maior] = aux;
    heapify(a, n, maior);
  }
}

void buildHeap(int *a, int n) {
  int i;
  for(i = (n - 1) / 2; i >= 0; i--) heapify(a, n, i);
}

void heapSort(int *a, int n) {
  int i, aux;
  buildHeap(a, n);
  for(i = n - 1; i > 0; i--) {
    aux = a[0];
    a[0] = a[i];
    a[i] = aux;
    heapify(a, i, 0);
  }
}

void printVet(int *a, int n) {
  printf("[");
  for(int i = 0; i < n - 1; i++) {
    printf("%d, ", a[i]);
  }
  printf("%d]", a[n - 1]);
  printf("\n");
}

void main() {
  int vet[] = {1, 6, 5, 3, 7, 8, 4, 2};
  // int vet[] = {1, 1, 1, 1, 1, 1, 1, 1};
  heapSort(vet, 8);
}
