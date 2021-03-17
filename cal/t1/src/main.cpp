#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "encryption.hpp"
#include "key_generator.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void print_file(std::string file_name) {
  std::ifstream is(file_name, std::ifstream::binary);
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

  cout << "Conteudo " << file_name << "{\n" << buffer << "\n}" << endl;

  delete[] buffer;
  is.close();
}

void write_in_file(std::string file_name, std::string content) {
  std::ofstream ws(file_name, std::ios::out | std::ios::binary);
  if(!ws) {
    std::cerr << "Erro ao abrir o arquivo de saida" << std::endl;
    exit(EXIT_FAILURE);
  }

  ws.write(content.c_str(), content.length());

  ws.close();
}

int main(int argc, char const *argv[]) {
  // o nome do arquivo será passado via parametro
  if(argc != 1) {
    std::cerr << "Quantidade de argumentos errada" << std::endl;
    exit(EXIT_FAILURE);
  }

  // initialize_ll();

  std::string s = "Olá pessoas, tudo bem?\nEu vou bem também.";

  write_in_file("og.bin", s);
  print_file("og.bin");
  encrypt_file("og.bin", "out.bin");
  print_file("out.bin");
  decrypt_file("out.bin", "dec.bin");
  print_file("dec.bin");
}
