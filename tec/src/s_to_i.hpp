#ifndef S_TO_I_HPP
#define S_TO_I_HPP

#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> quintuple;
std::string left_limit("§");
std::string right_limit("£");

bool q_already_exists(std::vector<quintuple> &m, quintuple q_) {
  for(auto &q : m) {
    if(q == q_) return true;
  }
  return false;
}

bool is_in_alphabet(std::vector<std::string> a, std::string c) {
  for(auto &s : a) {
    if(s == c) return true;
  }
  return false;
}

std::vector<quintuple> s_to_i(std::vector<quintuple> m) {
  std::cout << "Sipser to DI" << std::endl;
  std::vector<quintuple> m_new;

  // primeiro passo é renomear o estado inicial de '0' para '0inicial'
  for(auto &q : m) {
    if(q[0] == "0") q[0] = "0inicial";
    if(q[4] == "0") q[4] = "0inicial";
  }

  // movimenta para a esquera e insere o 'left_limit'
  // entao volta para a direita e vai para o estado inicial real
  m_new.push_back(quintuple{"0", "*", "*", "l", "limitaux"});
  m_new.push_back(quintuple{"limitaux", "_", left_limit, "r", "0inicial"});

  // para toda quintupla com movimento para esquerda:
  // cria-se uma transição reflexiva do estado de destino desta quint
  // lendo e escrevendo o simbolo 'left_limit' e indo para direita
  for(auto &q : m) {
    if(q[3] == "l" && q[4] != "halt-accept") {
      quintuple tmp{q[4], left_limit, left_limit, "r", q[4]};
      if(!q_already_exists(m_new, tmp)) m_new.push_back(tmp);
    }
  }

  // coloca o resto de m no m_new
  for(auto &q : m) {
    m_new.push_back(q);
  }

  return m_new;
}

#endif