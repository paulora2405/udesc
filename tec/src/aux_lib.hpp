#ifndef AUX_LIB_HPP
#define AUX_LIB_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &text) {
  std::string tmp;
  std::vector<std::string> stk;
  std::stringstream ss(text);
  while(getline(ss, tmp, ' ')) {
    stk.push_back(tmp);
  }
  return stk;
}

void print_machine(std::vector<std::string> &m) {
  for(auto &q : m) {
    for(auto &e : q) {
      std::cout << e << ' ';
    }
    std::cout << std::endl;
  }
}

void replace_underlines(std::vector<std::vector<std::string>> &m) {
  // nome de estado nao pode conter '-'
  size_t i;
  for(auto &q : m) {
    for(auto &e : q) {
      while((i = e.find('-')) != std::string::npos) {
        e.replace(i, 1, "_");
      }
    }
  }
}

void gerar_dot(std::vector<std::vector<std::string>> m, std::string filename) {
  std::cout << "Gerando o arquivo " << filename << ".dot" << std::endl;
  std::ofstream ws("dot/" + filename + ".dot");
  if(!ws.is_open()) {
    std::cerr << "Erro ao abrir o arquivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }
  ws << "digraph " << filename << " {\n";
  ws << "\trankdir=LR\n";
  ws << "\tnode [shape=circle, fixedsize=false, width=0.7]\n";
  ws << "\t	edge [color=lightslategray]\n\n";
  replace_underlines(m);
  for(auto &q : m) {
    if(q[4] == "halt_accept") {
      ws << "\t\"" << q[4]
         << "\" [shape=doublecircle, style=filled, color=red, fillcolor=whitesmoke]\n";
    }
    std::string t = "\t\"" + q[0] + "\"" + "->\"" + q[4] + "\"" + " [label=\"" + q[1] + " -> " +
                    q[2] + ", " + q[3] + "\"];";
    ws << t << '\n';
  }
  ws << "\n}" << std::flush;
  ws.close();
}

#endif