#include <stdio.h>
#include <stdlib.h>

// QUESTAO 1 - FIBONACCI LINEAR obs: para a coleta de dados foi feito um programa comparando as duas
// funções e exportando para um arquivo .csv
int fib_linear(int n) {
  if(n < 2) return n;

  int n1 = 0, n2 = 1, result = 0;

  for(int i = 2; i <= n; i++) {
    result = n1 + n2;
    n1 = n2;
    n2 = result;
  }

  return n2;
}

// QUESTAO 5 - INSERÇÃO NA CABEÇA E CAUDA
struct Lista {
  int elem;
  struct Lista *ptr;
};

struct Lista *head = NULL;

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

// QUESTAO 6 - IMPRIMIR SEM RECURSÃO
struct Arvore {
  int elem;
  struct Arvore *esq, *dir;
};

struct Pilha {
  struct Arvore *nodo;
  struct Pilha *next;
};

int isEmpty(struct Pilha *topo) { return (topo == NULL) ? 1 : 0; }

void push(struct Pilha **topo, struct Arvore *nodo) {
  struct Pilha *nodo_new = (struct Pilha *)malloc(sizeof(struct Pilha));

  if(nodo_new == NULL) {
    printf("Stack Overflow \n");
    getchar();
    exit(0);
  }

  nodo_new->nodo = nodo;

  nodo_new->next = (*topo);

  (*topo) = nodo_new;
}

struct Arvore *pop(struct Pilha **topo) {
  struct Arvore *res;
  struct Pilha *top;

  if(isEmpty(*topo)) {
    printf("Stack Underflow \n");
    getchar();
    exit(1);
  } else {
    top = *topo;
    res = top->nodo;
    *topo = top->next;
    free(top);
    return res;
  }
}

void imprimirRecursiva(struct Arvore *r) {
  if(r != NULL) {
    imprimir(r->esq);
    printf("%d ", r->elem);
    imprimir(r->dir);
  }
}

void imprimirIterativa(struct Arvore *raiz) {
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