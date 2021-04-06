#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aux_lib.hpp"
#include "i_to_s.hpp"
#include "s_to_i.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char const *argv[]) {
  if(argc != 2) {
    std::cerr << "Passe apenas o nome do arquivo como argumento!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // recebe o nome do arquivo como parametro na execução
  string filename = string(argv[1]);
  std::ifstream is(filename);
  if(!is.is_open()) {
    std::cerr << "Erro ao abrir o arquivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }

  // cria um buffer para leitura do arquivo
  char *buffer = new char[1024];

  // le a primeira linha para definir o tipo de fita
  is.getline(buffer, 1024);
  string tape_type = string(buffer);

  // le as demais linhas
  vector<vector<string>> movements;
  while(!is.eof()) {
    is.getline(buffer, 1024);
    // ignora linhas vazias e.g. ultima linha em branco
    if(!string(buffer).empty()) {
      movements.push_back(split(string(buffer)));
    }
  }
  is.close();
  delete[] buffer;

  // gera arquivo .dot da entrada
  gerar_dot(movements, "entrada");

  // seleciona a conversao correta
  switch(tape_type[1]) {
    case 'I':
      movements = i_to_s(movements);
      tape_type[1] = 'S';
      break;
    case 'S':
      movements = s_to_i(movements);
      tape_type[1] = 'I';
      break;
    default:
      std::cerr << "Tipo não reconhecido" << std::endl;
      exit(EXIT_FAILURE);
  }

  // escreve para o output
  std::ofstream ws("output.txt");
  if(!ws.is_open()) {
    std::cerr << "Erro ao abrir o arquivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }
  ws << tape_type << endl;
  for(auto &q : movements) {
    bool first = true;
    for(auto &e : q) {
      if(!first) ws << ' ';
      ws << e;
      first = false;
    }
    ws << endl;
  }
  ws.close();

  // gera arquivo .dot da saida
  gerar_dot(movements, "saida");
}
