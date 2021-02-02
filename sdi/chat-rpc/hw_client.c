#include <rpc/rpc.h>
#include <stdio.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

static int id;
int contador_msg = 0;

int main(int argc, char *argv[]) {
  // Estrutura RPC de comunicação
  CLIENT *cl;

  // Arquivo local
  FILE *file;

  // Parâmetros das funçcões
  // Nickname e conteudo do arquivo
  struct param2 par_f2;
  // par_f2.nick = (char *)malloc(128 * sizeof(char));
  // par_f2.content = (char *)malloc(1024 * 1024 * sizeof(char));

  struct param3 par_f4;

  // Retorno das funções
  int *ret_f1 = NULL;
  int *ret_f2 = NULL;
  struct return1 *ret_f4 = NULL;

  // Verificação dos parâmetros oriundos da console
  if(argc != 2) {
    printf("ERRO: ./client <hostname>\n");
    exit(1);
  }

  // Conexão com servidor RPC
  cl = clnt_create(argv[1], PROG, VERS, "tcp");
  if(cl == NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  // Atribuições de valores para os parâmetros
  printf("Digite seu apelido: ");
  scanf("%s", &par_f2.nick);

  // Se comunica com o server e recebe um id unico
  ret_f1 = func1_1(NULL, cl);
  if(ret_f1 == NULL) {
    clnt_perror(cl, argv[1]);
    exit(1);
  }
  id = *ret_f1;

  // Main Loop de execucao
  int op = -1;
  while(op != 0) {
    printf("\nOperacoes possiveis:\n1- Enviar o arquivo\n2- Receber o arquivo\n0- Sair\n");
    scanf("%d", &op);
    switch(op) {
      // CASO 1 -> ************** ENVIAR ARQUIVO **************
      case 1:

        // requisita o nome e abre o arquivo
        printf("Digite o nome do arquivo a ser enviado: ");
        char file_name[256];
        scanf("%s", file_name);
        file = fopen(file_name, "r");
        if(file == NULL) {
          printf("Error: Na abertura do arquivo (%s)\n", file_name);
          exit(1);
        }
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file)) {
          sprintf(par_f2.content, "%s%s", par_f2.content, buffer);
        }
        fclose(file);

        // envia o nickname (par_f1) e o conteudo do arquivo (par_f2) para o servidor
        ret_f2 = func2_1(&par_f2, cl);
        if(ret_f2 == NULL) {
          clnt_perror(cl, argv[1]);
          exit(1);
        }

        strcpy(par_f2.content, "");

        printf("Arquivo enviado com sucesso\n");

        break;

      // CASO 2 -> ************** RECEBER ARQUIVO **************
      case 2:

        par_f4.cont_client_side = contador_msg;
        strcpy(par_f4.nick_client_side, par_f2.nick);

        ret_f4 = func4_1(&par_f4, cl);
        if(ret_f4 == NULL) {
          clnt_perror(cl, argv[1]);
          exit(1);
        }

        printf("ret_f4 = %d\n", ret_f4->campo_vali);

        if(ret_f4->campo_vali == 0) {
          printf("Nao ha novas mensagems\n");
          break;
        } else if(ret_f4->campo_vali == 2) {
          contador_msg++;
          printf("O chat %d eh de sua autoria\n", contador_msg);
          break;
        } else if(ret_f4->campo_vali == 1) {
          if(strcmp(ret_f4->content, "") == 0) {
            printf("Nao ha conteudo no arquivo\n");
          } else {
            FILE *file_received;
            char file_name[256];
            sprintf(file_name, "%s-%d.client%d", par_f2.nick, ++contador_msg, id);

            file_received = fopen(file_name, "w");
            if(file_received == NULL) {
              printf("Error: Na abertura do arquivo (%s)\n", file_name);
              exit(0);
            }
            fputs(ret_f4->content, file_received);
            fclose(file_received);

            printf("Arquivo %s recebido com sucesso (chat %d)\n", file_name, contador_msg);
          }
        }

        break;

      case 0:
        break;

      default:
        printf("Operacao nao reconhecida\n");
        break;
    }
  }

  return 0;
}
