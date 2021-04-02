#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> split(const string &text) {
  string tmp;
  vector<string> stk;
  std::stringstream ss(text);
  while(getline(ss, tmp, ' ')) {
    stk.push_back(tmp);
  }
  return stk;
}

int main(int argc, char const *argv[]) {
  if(argc != 2) {
    std::cerr << "Passe apenas o nome do arquivo como argumento!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // recebe o nome do arquivo como parametro na execução
  string filename = string(argv[1]);
  std::ifstream is(filename);

  // cria um buffer para leitura do arquivo
  char *buffer = new char[1024];

  // le a primeira linha para definir o tipo de fita
  is.getline(buffer, 1024);
  string tape_type = string(buffer);

  vector<vector<string>> quints;
  while(!is.eof()) {
    is.getline(buffer, 1024);
    quints.push_back(split(string(buffer)));
  }
  delete[] buffer;

  for(auto q : quints) {
    for(auto e : q) {
      cout << e << ' ';
    }
    cout << endl;
  }

  return 0;
}
