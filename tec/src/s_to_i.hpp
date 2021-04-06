#ifndef S_TO_I_HPP
#define S_TO_I_HPP

#include <iostream>
#include <string>
#include <vector>

std::string tape_left_limit_symbol("§");

std::vector<std::vector<std::string>> s_to_i(std::vector<std::vector<std::string>> m) {
  std::cout << "Sipser to DI" << std::endl;
  std::vector<std::vector<std::string>> m_new;
  std::vector<std::string> tmp_q;
  // estado inicial que se movimenta para a esquerda
  //  lendo e escrevendo qualquer coisa
  tmp_q.clear();
  tmp_q.push_back("ini");
  tmp_q.push_back("*");
  tmp_q.push_back("*");
  tmp_q.push_back("l");
  tmp_q.push_back("ini2");
  m_new.push_back(tmp_q);
  // estado auxiliar ao inicial que escreve
  //  o simbolo de limite a esqueda da fita
  tmp_q.clear();
  tmp_q.push_back("ini2");
  tmp_q.push_back("_");
  tmp_q.push_back(tape_left_limit_symbol);
  tmp_q.push_back("r");
  tmp_q.push_back(m.front().front());
  m_new.push_back(tmp_q);

  // coloca o resto de m no m_new
  for(auto q : m) {
    m_new.push_back(q);
  }

  return m_new;
}

#endif