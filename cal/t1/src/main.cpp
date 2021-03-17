#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "rsa_encription.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void read_test() {
  std::ifstream is("og.bin", std::ifstream::binary);
  if(!is) {
    cout << "Erro ao abrir o arquivo de entrada" << endl;
    exit(EXIT_FAILURE);
  }

  is.seekg(0, is.end);
  int len_is = is.tellg();
  is.seekg(0, is.beg);

  char *buffer = new char[len_is];
  cout << "Arquivo tem " << len_is << " caracteres" << endl;

  is.read(buffer, len_is);
  if(!is) {
    cout << "Erro ao ler o arquivo de entrada" << endl;
    exit(EXIT_FAILURE);
  }

  cout << buffer << endl;

  is.close();
  delete[] buffer;
}

void write_test() {
  std::ofstream ws("og.bin", std::ofstream::binary);
  if(!ws) {
    cout << "Erro ao abrir o arquivo de saida" << endl;
    exit(EXIT_FAILURE);
  }

  char *buffer = new char[1000];
  string s = "teste binário";

  ws.write(s.c_str(), 17);

  ws.close();
}

int main(int argc, char const *argv[]) {
  // o nome do arquivo será passado via parametro
  if(argc != 1) {
    cout << "Quantidade de argumentos errada\n";
    exit(1);
  }

  initialize_ll();

  write_test();
  read_test();
}
