#include <math.h>
#include <stdio.h>

#include <iostream>

int vetor_cidade[5] = {1, 2, 3, 4, 5};
int valor_cidade[5] = {2, 4, 8, 16, 32};
bool* visited = new bool[5];
int soma = 0;
int lista_cheia;

void arvore(int a, int distancia_origem) {
  int printado = 0;
  visited[a] = true;
  if(valor_cidade[a] != distancia_origem) soma += valor_cidade[a];
  for(int i = 0; i < 5; i++) {
    lista_cheia = 1;
    for(int i = 0; i < 5; i++) {
      if(visited[i] == false) {
        lista_cheia = 0;
        break;
      };
    }
    if(lista_cheia == 1 && printado == 0) {
      soma = soma + distancia_origem;
      std::cout << "Caminho: " << soma << std::endl;
      printado = 1;
    }
    if(visited[i] == false) {
      // std::cout << soma <<std::endl;
      for(int i = 0; i < 5; i++) { std::cout << visited[i] << " "; }
      std::cout << std::endl;
      arvore(i, distancia_origem);
      visited[i] = false;
      // soma -= valor_cidade[i];
    }
  }

  soma = 0;
}

int main(int argc, char const* argv[]) {
  arvore(0, 2);
  int a = 2;
}