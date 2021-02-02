#include <rpc/rpc.h>

#include "hw.h"

struct file_meta {
  int chat_num;
  char sender_nick[128];
};

static int id = 0;
static int contador_msg = 0;

// para fins de simplicidade, o chat RPC tem um hardlimit de 200 mensagens devido ao uso de uma
// estrutura de dados de tamanho fixo
struct file_meta arquivos[200];

// funcao 1
// primeira comunicacao do cliente com o servidor
// retorna o id de um cliente fazendo sua primeira comunicacao
int *func1_1_svc(void *a, struct svc_req *req) {
  // static int ret = id++;
  id++;
  printf("Cliente com id %d comunicou-se\n", id);
  return (&id);
}

// funcao 2
// recebe o conteudo do arquivo e escreve em uma copia local
// retorna um int nao nulo qualquer
int *func2_1_svc(struct param2 *par, struct svc_req *req) {
  printf("%s acessou func2\n", par->nick);
  static int ret = 1;
  FILE *file_local_cpy;
  char file_name[256];

  sprintf(file_name, "%s-%d.serv", par->nick, ++contador_msg);

  file_local_cpy = fopen(file_name, "w");
  if(file_local_cpy == NULL) {
    printf("Error: Na abertura do arquivo (%s)\n", file_name);
    exit(1);
  }
  fputs(par->content, file_local_cpy);
  fclose(file_local_cpy);

  arquivos[contador_msg - 1].chat_num = contador_msg;
  strcpy(arquivos[contador_msg - 1].sender_nick, par->nick);

  printf("Arquivo recebido\tOrigem: %s\n", par->nick);

  return (&ret);
}

// funcao 4
// faz verificoes no pedido do cliente
// > verifica qual chat o cliente precisa
// > verifica se o chat que o cliente precisa nao foi enviado por ele mesmo
// > verifica se o chat que o cliente precisa ja existe (se o contador_server >= contador_client)
struct return1 *func4_1_svc(struct param3 *par, struct svc_req *req) {
  // return1 tem 2 campos:
  //    campo1 -> campo de validacao (se o nick do chat nao eh igual ao nick do cliente que pede)
  //       0 nao ha nova mensagem; 1 ha nova mensagem; 2 ha nova mensagem porem autor eh o cliente
  //    campo2 -> conteudo do arquivo (NULO se o campo1 for falso)

  // param3 tem 2 campos:
  //    campo1 -> contagem de mensagens do lado do client (deve ser menor que a do server para o
  //       cliente ser elegivel a receber a mensagem)
  //    campo2 -> nick do client

  static struct return1 ret;

  // compara se o cliente nao esta atualizado com os novos chats
  if(par->cont_client_side < contador_msg) {
    // compara o nick do autor do arquivo com o nick do client requisitando
    int compare = strcmp(arquivos[par->cont_client_side].sender_nick, par->nick_client_side);

    if(compare == 0) {
      ret.campo_vali = 2;
      strcpy(ret.content, "");

      return (&ret);
    }

    char file_name[256];
    sprintf(file_name, "%s-%d.serv", arquivos[par->cont_client_side].sender_nick,
            arquivos[par->cont_client_side].chat_num);

    FILE *file_local;
    file_local = fopen(file_name, "r");
    if(file_local == NULL) {
      printf("Error: Na abertura do arquivo (%s)\n", file_name);
      exit(1);
    }

    char msg[1024 * 1024] = "";
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), file_local)) {
      sprintf(msg, "%s%s", msg, buffer);
    }

    strcpy(ret.content, msg);
    ret.campo_vali = 1;

    return (&ret);

  } else {
    ret.campo_vali = 0;
    strcpy(ret.content, "");

    return (&ret);
  }
}