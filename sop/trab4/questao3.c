#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Requisicao {
  int blocoInicial;
  int numDeBlocos;
  char operacao;
} Requisicao;

extern int errno;
Requisicao *req;
int qntReq = 0;
int fundiu;

void removeReqDuplicada();

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

/*---------------------------------------------------------------*/
void fundirR(Requisicao in) {
  // removeReqDuplicada();

  int diferencaDeBlocos;
  int inBlocoFinal = in.blocoInicial + in.numDeBlocos;
  int reqBlocoFinal;

  for(int i = 0; i < qntReq; i++) {
    //

    if(in.operacao != req[i].operacao) continue;

    if(in.blocoInicial == req[i].blocoInicial && in.numDeBlocos == req[i].numDeBlocos) return;

    reqBlocoFinal = req[i].blocoInicial + req[i].numDeBlocos;
    diferencaDeBlocos = abs(in.blocoInicial - req[i].blocoInicial);

    if(in.blocoInicial < req[i].blocoInicial) {
      //
      if(inBlocoFinal >= req[i].blocoInicial) {
        req[i].blocoInicial = in.blocoInicial;

        if(req[i].numDeBlocos + diferencaDeBlocos >= in.numDeBlocos) {
          if(req[i].numDeBlocos + diferencaDeBlocos <= 64)
            req[i].numDeBlocos = req[i].numDeBlocos + diferencaDeBlocos;
          else
            return;
        } else
          req[i].numDeBlocos = in.numDeBlocos;

        fundiu = 1;
        fundirR(req[i]);
      }
    } else if(in.blocoInicial >= req[i].blocoInicial) {
      //
      if(reqBlocoFinal >= in.blocoInicial) {
        req[i].blocoInicial = req[i].blocoInicial;

        if(in.numDeBlocos + diferencaDeBlocos >= req[i].numDeBlocos) {
          if(in.numDeBlocos + diferencaDeBlocos <= 64)
            req[i].numDeBlocos = in.numDeBlocos + diferencaDeBlocos;
          else
            return;

        } else
          req[i].numDeBlocos = req[i].numDeBlocos;

        fundiu = 1;
        fundirR(req[i]);
      }
    }
  }
  return;
}

/*---------------------------------------------------------------*/
void fundirW(Requisicao in) {
  int diferencaDeBlocos;
  int inBlocoFinal = in.blocoInicial + in.numDeBlocos;
  int reqBlocoFinal;

  for(int i = 0; i < qntReq; i++) {
    //

    if(in.operacao != req[i].operacao) continue;

    if(in.blocoInicial == req[i].blocoInicial && in.numDeBlocos == req[i].numDeBlocos) return;

    reqBlocoFinal = req[i].blocoInicial + req[i].numDeBlocos;
    diferencaDeBlocos = abs(in.blocoInicial - req[i].blocoInicial);

    if(in.blocoInicial < req[i].blocoInicial) {
      //
      if(inBlocoFinal == req[i].blocoInicial) {
        req[i].blocoInicial = in.blocoInicial;

        if(req[i].numDeBlocos + diferencaDeBlocos >= in.numDeBlocos) {
          if(req[i].numDeBlocos + diferencaDeBlocos <= 64)
            req[i].numDeBlocos = req[i].numDeBlocos + diferencaDeBlocos;
          else
            return;
        } else
          req[i].numDeBlocos = in.numDeBlocos;

        fundiu = 1;
        fundirR(req[i]);
      }
    } else if(in.blocoInicial >= req[i].blocoInicial) {
      //
      if(reqBlocoFinal == in.blocoInicial) {
        req[i].blocoInicial = req[i].blocoInicial;

        if(in.numDeBlocos + diferencaDeBlocos >= req[i].numDeBlocos) {
          if(in.numDeBlocos + diferencaDeBlocos <= 64)
            req[i].numDeBlocos = in.numDeBlocos + diferencaDeBlocos;
          else
            return;

        } else
          req[i].numDeBlocos = req[i].numDeBlocos;

        fundiu = 1;
        fundirR(req[i]);
      }
    }
  }
  return;
}

/*---------------------------------------------------------------*/
void escalonador(Requisicao in) {
  fundiu = 0;
  if(in.operacao == 'w') {
    fundirW(in);
  } else
    fundirR(in);
  if(fundiu == 0) {
    req = realloc(req, sizeof(Requisicao) * ++qntReq);
    if(req == NULL) {
      free(req);
      perror("Erro na realocação de memória");
      exit(EXIT_FAILURE);
    }
    req[qntReq - 1] = in;
  }
  removeReqDuplicada();
}

/*---------------------------------------------------------------*/
void removeReqDuplicada() {
  int req1BlocoFinal;
  int req2BlocoFinal;

  for(int i = 0; i < qntReq; i++) {
    req1BlocoFinal = req[i].blocoInicial + req[i].numDeBlocos;
    for(int j = 0; j < qntReq; j++) {
      req2BlocoFinal = req[j].blocoInicial + req[j].numDeBlocos;

      if(req[i].operacao != req[j].operacao || i == j || req[i].operacao == 'w' ||
         req[j].operacao == 'w')
        continue;

      if(req[i].blocoInicial <= req[j].blocoInicial && req1BlocoFinal >= req2BlocoFinal) {
        int k;
        for(k = j; k < qntReq - 1; k++) {
          req[k] = req[k + 1];
        }
        req = realloc(req, sizeof(Requisicao) * --qntReq);
        if(req == NULL) {
          free(req);
          perror("Erro na realocação de memória");
          exit(EXIT_FAILURE);
        }
        return;
      }
    }
  }

  // 100 11
  // 101 10
}

/*---------------------------------------------------------------*/
int main() {
  Requisicao in = {0};

  while(in.blocoInicial >= 0) {
    scanf("%d", &in.blocoInicial);
    if(in.blocoInicial > -1) {
      scanf("%d %c", &in.numDeBlocos, &in.operacao);
      if(in.operacao != 'r' && in.operacao != 'w') {
        free(req);
        exit(EXIT_FAILURE);
      };
      escalonador(in);
    }
  }

  qsort(req, qntReq, sizeof(Requisicao), compare);

  for(int i = 0; i < qntReq; i++) {
    printf("%d %d %c\n", req[i].blocoInicial, req[i].numDeBlocos, req[i].operacao);
  }

  free(req);
}
