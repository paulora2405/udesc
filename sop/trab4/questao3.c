#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

typedef struct {
  int blocoInicial;
  int numDeBlocos;
  char operacao;
} Requisicao;

void escalonador(Requisicao requisoes[], int qntReq) {
  for(int i = 0; i < qntReq; i++) {
    printf("%d %d %c\n", requisoes[i].blocoInicial, requisoes[i].numDeBlocos, requisoes[i].operacao);
  }
}

int main(int argc, char *argv[]) {
  Requisicao in = {0};
  int qntReq = 0;
  Requisicao *requisicoes;  // = NULL;
  // requisicoes = malloc(sizeof(Requisicao) * qntReq);

  while(in.blocoInicial != -1) {
    scanf("%d", &in.blocoInicial);
    if(in.blocoInicial != -1) {
      scanf("%d %c", &in.numDeBlocos, &in.operacao);
      requisicoes = realloc(requisicoes, sizeof(Requisicao) * ++qntReq);
      if(requisicoes == NULL) {
        free(requisicoes);
        perror("Erro na realocação de memória");
        exit(EXIT_FAILURE);
      }
      requisicoes[qntReq - 1].blocoInicial = in.blocoInicial;
      requisicoes[qntReq - 1].numDeBlocos = in.numDeBlocos;
      requisicoes[qntReq - 1].operacao = in.operacao;
    }
  }

  escalonador(requisicoes, qntReq);

  free(requisicoes);
}
