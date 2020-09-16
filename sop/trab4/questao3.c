#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

typedef struct {
  int blocoInicial;
  int numDeBlocos;
  char operacao;
} Requisicao;

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
// qsort(requisicoes, qntReq, sizeof(Requisicao), compare);

int escalonador(Requisicao in, Requisicao requisicoes[], int qntReq) {
  while(fundirReq(in, requisicoes, qntReq) != qntReq) {}

  // requisicoes = realloc(requisicoes, sizeof(Requisicao) * qntReq);
  // if(requisicoes == NULL) { return -1; }
  requisicoes[qntReq - 1] = in;
  return qntReq;
}

int fundirReq(Requisicao in, Requisicao req[], int qntReq) {
  int sobreposicaoDeBlocos;
  for(int i = 0; i < qntReq - 1; i++) {
    if(in.operacao == req[i].operacao && in.operacao == 'r') {
      if(in.blocoInicial < req[i].blocoInicial) {
        sobreposicaoDeBlocos = in.blocoInicial + in.numDeBlocos - req[i].blocoInicial;
        if(sobreposicaoDeBlocos >= 0) {
          int diferencaDeBlocos = req[i].blocoInicial - in.blocoInicial;
          req[i].blocoInicial = in.blocoInicial;

          if(req[i].numDeBlocos + diferencaDeBlocos >= in.numDeBlocos)
            req[i].numDeBlocos = req[i].numDeBlocos + diferencaDeBlocos;
          else
            req[i].numDeBlocos = in.numDeBlocos;

          return qntReq - 1;
        }
      } else if(in.blocoInicial >= req[i].blocoInicial) {
        sobreposicaoDeBlocos = req[i].blocoInicial + req[i].numDeBlocos - in.blocoInicial;
        if(sobreposicaoDeBlocos >= 0) {
          int diferencaDeBlocos = in.blocoInicial - req[i].blocoInicial;
          req[i].blocoInicial = req[i].blocoInicial;

          if(req[i].numDeBlocos >= in.numDeBlocos + diferencaDeBlocos)
            req[i].numDeBlocos = req[i].numDeBlocos;
          else
            req[i].numDeBlocos = in.numDeBlocos + diferencaDeBlocos;

          return qntReq - 1;
        }
      }
    }
  }
  return qntReq;
}

void removeReqDuplicada(Requisicao req[], int qntReq) {}

int main() {
  Requisicao in = {0};
  int qntReq = 0;

  // Requisicao *requisicoes;
  Requisicao requisicoes[20];

  while(in.blocoInicial >= 0) {
    scanf("%d", &in.blocoInicial);
    if(in.blocoInicial != -1) {
      scanf("%d %c", &in.numDeBlocos, &in.operacao);
      if(in.operacao != 'r' && in.operacao != 'w') { exit(EXIT_FAILURE); };
      qntReq = escalonador(in, requisicoes, ++qntReq);
      if(qntReq == -1) {
        // free(requisicoes);
        perror("Erro na realocação de memória");
        exit(EXIT_FAILURE);
      }
    }
  }

  for(int i = 0; i < qntReq; i++) {
    printf("%d %d %c\n", requisicoes[i].blocoInicial, requisicoes[i].numDeBlocos,
           requisicoes[i].operacao);
  }

  // free(requisicoes);
}
