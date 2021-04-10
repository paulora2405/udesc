#include "../include/file_manipulation.hpp"

void print_file(std::string file_name) {
  std::ifstream is(file_name, std::ios::in | std::ios::binary);
  if(!is.is_open()) {
    std::cout << "Erro ao abrir o arquivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }

  is.seekg(0, is.end);
  int len = is.tellg();
  is.seekg(0, is.beg);

  char *buffer = new char[len];
  std::cout << "Arquivo tem " << len << " bytes" << std::endl;

  is.read(buffer, len);

  std::cout << "Conteudo " << file_name << "{" << std::endl;
  std::cout << buffer << "\n}" << std::endl;

  delete[] buffer;
  is.close();
}

void write_file(std::string file_name, std::string content) {
  std::ofstream ws(file_name, std::ios::out | std::ios::binary);
  if(!ws.is_open()) {
    std::cerr << "Erro ao abrir o arquivo de saida" << std::endl;
    exit(EXIT_FAILURE);
  }

  char *string_c = new char[content.length()];
  for(unsigned long int i = 0; i < content.length(); i++) {
    string_c[i] = content[i];
  }

  for(unsigned long int i = 0; i < content.length(); i++) {
    ws.write(&string_c[i], sizeof(string_c[0]));
  }

  delete[] string_c;
  ws.close();
}
