#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int errno;
int npf;
int cnt_fifo = 0;
int cnt_mru = 0;

typedef struct {
  long int pl;
  unsigned short int valido;
  long int t;
} Pf;

int max(Pf lista[]) {
  int max[2] = {-1, -1};  //indice 0 = tempo maximo, indice 1 = posicao no vetor
  for(int i = 0; i < npf; i++) {
    if(lista[i].t > max[0]) {
      max[0] = lista[i].t;
      max[1] = i;
    }
  }
  return max[1];
}

void mru_(Pf mru[], int pl) {
  short int found = 0;

  for(int i = 0; i < npf; i++) {  //procura na mem fisica
    if(mru[i].valido == 1 && mru[i].pl == pl) {
      mru[i].t = 0;
      found = 1;  //found = 1 se achou na mem fisica
      break;
    }
  }
  if(found == 0) {  //falta de pagina
    cnt_mru++;
    for(int i = 0; i < npf; i++) {  //procura pf invalida
      if(mru[i].valido == 0) {
        mru[i].pl = pl;
        mru[i].valido = 1;
        mru[i].t = 0;  //qnd acessa, zera contador de tempo
        found = 2;     //found = 2 se faltou pagina mas achou pf invalida
        break;
      }
    }
    if(found == 0) {  //procura pf menos recentemente usada
      int i = max(mru);
      mru[i].pl = pl;
      mru[i].valido = 1;
      mru[i].t = 0;
    }
  }
  for(int i = 0; i < npf; i++) {
    mru[i].t++;
  }

  //debug e visualizacao
  // if(found != 1)
  // 	printf("MRU: (faltou pagina)\n");
  // else
  // 	printf("MRU:\n");
  // for(int i=0; i<npf; i++){
  // 	printf("%ld[v=%d;t=%ld]\t", mru[i].pl,mru[i].valido,mru[i].t);
  // }
  // printf("\n");
}

void fifo_(Pf fifo[], int pl) {
  short int found = 0;

  for(int i = 0; i < npf; i++) {  //procura na mem fisica
    if(fifo[i].valido == 1 && fifo[i].pl == pl) {
      found = 1;  //found = 1 se achou na mem fisica
      break;
    }
  }
  if(found == 0) {  //falta de pagina
    cnt_fifo++;
    for(int i = 0; i < npf; i++) {  //procura pf invalida
      if(fifo[i].valido == 0) {
        fifo[i].pl = pl;
        fifo[i].valido = 1;
        fifo[i].t = 0;
        found = 2;  //found = 2 se faltou pagina mas achou pf invalida
        break;
      }
    }
    if(found == 0) {  //procura pf mais velha
      int i = max(fifo);
      fifo[i].pl = pl;
      fifo[i].valido = 1;
      fifo[i].t = 0;
    }
  }

  for(int i = 0; i < npf; i++) {
    fifo[i].t++;
  }

  //debug e visualizacao
  // if(found != 1)
  // 	printf("FIFO: (faltou pagina)\n");
  // else
  // 	printf("FIFO:\n");
  // for(int i=0; i<npf; i++){
  // 	printf("%ld[v=%d;t=%ld]\t", fifo[i].pl,fifo[i].valido,fifo[i].t);
  // }
  // printf("\n");
}

int main(int argc, char *argv[]) {
  //argv[0] eh o nome do programa
  if(argv[1] == NULL || atoi(argv[1]) < 1) {  //verifica se a entrada existe e eh maior que 0
    errno = EIO;                              //erro de io
    perror("Entrada invalida\n");
    return -1;
  }
  npf = atoi(argv[1]);

  Pf fifo[npf];
  Pf mru[npf];

  for(int i = 0; i < npf; i++) {
    fifo[i].valido = 0;
    mru[i].valido = 0;
    // fifo[i].t = 0; //para debug e visualizacao
    // mru[i].t = 0; //para debug e visualizacao
    // fifo[i].pl = -1; //para debug e visualizacao
    // mru[i].pl = -1; //para debug e visualizacao
  }

  long int in;
  scanf("%ld", &in);
  while(in > -1 && in < npf * 10) {  //espaco de enderecamento virtual 10*npf
    fifo_(fifo, in);
    mru_(mru, in);
    scanf("%ld", &in);
  }
  if(in != -1) {  //se a ultima entrada nao foi -1, cancela a execucao
    errno = EIO;  //erro de io
    perror("Entrada invalida\n");
    return -1;
  }

  printf("\nFIFO:\t%d faltas de paginas\n", cnt_fifo);
  printf("MRU:\t%d faltas de paginas\n", cnt_mru);

  return 0;
}