#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

// compile:
// clear; gcc questao3.c -o main; ./main < in.txt

typedef struct {
  int blocoInicial;
  int numDeBlocos;
  char operacao;
} Requisicao;

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void escalonador(Requisicao requisicoes[], int qntReq) {
  qsort(requisicoes, qntReq, sizeof(Requisicao), compare);

  Requisicao *copiaFundidada;

  for(int i = 0; i < qntReq; i++) {
    int sobreposicaoDeBlocos = -1;
    if(i + 1 < qntReq)
      sobreposicaoDeBlocos = requisicoes[i].blocoInicial + requisicoes[i].numDeBlocos - requisicoes[i + 1].blocoInicial;
    if(sobreposicaoDeBlocos >= 0 && requisicoes[i].operacao == requisicoes[i + 1].operacao) {
      // printf("Necessario fundir do bloco %d ao bloco %d\n", requisicoes[i].blocoInicial, requisicoes[i + 1].blocoInicial + requisicoes[i + 1].numDeBlocos);
      // TODO: verificar se nao passa de 64 blocos
      int diferencaEntreBlocos = requisicoes[i + 1].blocoInicial - requisicoes[i].blocoInicial;
      if(requisicoes[i].numDeBlocos > requisicoes[i + 1].numDeBlocos + diferencaEntreBlocos) {
        requisicoes[i + 1].numDeBlocos = requisicoes[i].numDeBlocos;
      } else {
        requisicoes[i + 1].numDeBlocos += diferencaEntreBlocos;
      }
      requisicoes[i + 1].blocoInicial = requisicoes[i].blocoInicial;
    }
  }

  for(int i = 0; i < qntReq; i++)
    printf("%d %d %c\n", requisicoes[i].blocoInicial, requisicoes[i].numDeBlocos, requisicoes[i].operacao);
}

int main(int argc, char *argv[]) {
  Requisicao in = {0};
  int qntReq = 0;
  Requisicao *requisicoes;

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

      requisicoes[qntReq - 1] = in;
      // requisicoes[qntReq - 1].blocoInicial = in.blocoInicial;
      // requisicoes[qntReq - 1].numDeBlocos = in.numDeBlocos;
      // requisicoes[qntReq - 1].operacao = in.operacao;
    }
  }

  escalonador(requisicoes, qntReq);

  free(requisicoes);
}
