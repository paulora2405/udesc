#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Lista {
  int elem;
  struct Lista *ptr;
};

struct Lista *head = NULL;

void ex1();

void ex5();

void main() {
  int op;
  do {
    printf("Digite o numero para executar a função dos exercicios:\n");
    printf("1- Sequencia de fibonatti\n");
    printf("5- Sequencia de fibonatti\n");
    scanf("%d", &op);
    switch(op) {
      case 1:
        ex1();
        break;
      case 5:
        ex5();
        break;

      default:
        op = 0;
        break;
    }
  } while(op != 0);
}

int fib_linear(int quant) {
  if(quant < 2) return quant;
  int n1 = 0, n2 = 1, result = 0;
  for(int i = 2; i <= quant; i++) {
    result = n1 + n2;
    n1 = n2;
    n2 = result;
  }
  return n2;
}

int fib_recursiva(int quant) {
  if(quant < 2) return quant;
  return fib_recursiva(quant - 2) + fib_recursiva(quant - 1);
}

void ex1() {
  FILE *f;
  f = fopen("saida_ex1.csv", "w");
  fprintf(f, "Tempo fibonacci linear,");
  for(int i = 0; i < 46; i++) {
    clock_t Ticks[2];
    Ticks[0] = clock();
    fib_linear(i);
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    fprintf(f, "%f,", Tempo);
  }
  fprintf(f, "\nTempo fibonacci recurssiva,");
  for(int i = 0; i < 46; i++) {
    clock_t Ticks[2];
    Ticks[0] = clock();
    fib_recursiva(i);
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    fprintf(f, "%f,", Tempo);
  }
  getchar();
  fclose(f);
}

void insereNaCabeca(int novo_elemento) {
  struct Lista *node_new = (struct Lista *)malloc(sizeof(struct Lista));

  node_new->elem = novo_elemento;
  node_new->ptr = head;

  head = node_new;
}

void insereNaCauda(int novo_elemento) {
  struct Lista *node_new = (struct Lista *)malloc(sizeof(struct Lista));
  node_new->elem = novo_elemento;
  node_new->ptr = NULL;

  struct Lista *atual = head;

  while(atual->ptr != NULL) {
    atual = atual->ptr;
  }

  atual->ptr = node_new;
}

void imprimeLista() {
  struct Lista *atual = head;
  printf("\n[ ");

  while(atual != NULL) {
    printf("(%d)->", atual->elem);
    atual = atual->ptr;
  }

  printf(" ]\n");
}

void ex5() {
  insereNaCabeca(21);
  insereNaCabeca(5);
  insereNaCauda(7);
  imprimeLista();
}

void imprimirIterativa(struct Arvore *raiz) {
  struct Arvore {
    int elem;
    struct Arvore *esq, *dir;
  };

  struct Arvore *atual = raiz;
  struct Pilha *pilha = NULL;
  int acabou = 0;

  while(!acabou) {
    if(atual != NULL) {
      push(&pilha, atual);
      atual = atual->esq;
    }

    else {
      if(!isEmpty(pilha)) {
        atual = pop(&pilha);
        printf("%d ", atual->elem);

        atual = atual->dir;
      } else
        acabou = 1;
    }
  }
}