#ifndef I_TO_S_HPP
#define I_TO_S_HPP

#include <iostream>
#include <string>
#include <vector>

#include "s_to_i.hpp"

std::vector<quintuple> i_to_s(std::vector<quintuple> m) {
  std::cout << "DI to Sipser" << std::endl;
  std::vector<quintuple> m_new;

  // primeiro passo é renomear o estado inicial de '0' para '0inicial'
  for(auto &q : m) {
    if(q[0] == "0") q[0] = "0inicial";
    if(q[4] == "0") q[4] = "0inicial";
  }

  /*
   * estados auxiliares para o processo de inserir o
   * simbolo 'right_limit' no final do conteudo da fita a direita
   * e então deslocar todo o conteudo uma célula a direta,
   * até ler 2 _ seguidos, e então inserir o 'left_limit' na primeira célula
   */
  m_new.push_back(quintuple{"0", "*", "*", "r", "0"});
  m_new.push_back(quintuple{"0", "_", "_", "r", "0aux"});
  m_new.push_back(quintuple{"0aux", "_", right_limit, "l", "0aux2"});
  m_new.push_back(quintuple{"0aux2", "_", "_", "l", "0aux3"});
  m_new.push_back(quintuple{"0aux3", "0", "_", "r", "escreve0"});
  m_new.push_back(quintuple{"0aux3", "1", "_", "r", "escreve1"});
  m_new.push_back(quintuple{"0aux3", "_", left_limit, "r", "0inicial"});
  m_new.push_back(quintuple{"escreve0", "_", "0", "l", "0aux2"});
  m_new.push_back(quintuple{"escreve1", "_", "1", "l", "0aux2"});

  /*
    para toda quintupla com movimento para a direita:
    cria-se uma transição do estado de origem desta quint
    para um estado auxiliar que:
    caso leia o 'right_limit':
      acrescenta um branco no final da fita
    caso nao:
      simula movimento estacionario e vai para o estado de destino
   */

  for(auto &q : m) {
    if(q[3] == "r" && q[4] != "halt-accept") {
      // nomes dos estados auxiliares
      std::string name1 = "dir_" + q[0] + "_" + q[4];
      std::string name2 = "pushdir_" + q[0] + "_" + q[4];
      std::string name3 = "stopdir_" + q[0] + "_" + q[4];

      quintuple tmp1{q[0], q[1], q[2], "r", name1};
      quintuple tmp2{name1, right_limit, "_", "r", name2};
      quintuple tmp3{name2, "_", right_limit, "l", name1};
      quintuple tmp4{name1, "*", "*", "l", name3};
      quintuple tmp5{name3, "*", "*", "r", q[4]};

      if(!q_already_exists(m_new, tmp1)) m_new.push_back(tmp1);

      if(!q_already_exists(m_new, tmp2)) {
        m_new.push_back(tmp2);
        m_new.push_back(tmp3);
        m_new.push_back(tmp4);
        m_new.push_back(tmp5);
      }

      // marca a transição original para nao ser inserida
      q.push_back("marcada");
    }
  }

  /*
    para toda quintupla com movimento para a esquerda:
    cria-se uma transição do estado origem desta quint
    para um estado auxiliar que
    verifica se o simbolo lido é o 'left_limit'
    caso for:
      percorre toda fita para a direita até ler o 'right_limit'
      faz a operação de deslocar a fita uma célula a direita
      volta para a célula a direita do 'left_limit'
      continua execução
    caso não for:
      simula movimento estacionário e vai para o estado de destino
   */

  // criamos um alfabeto da fita para saber
  // todos os simbolos que podem ser escritos, com exceção dos 'limits'
  std::vector<std::string> tape_alphabet{"0", "1"};
  for(auto &q : m) {
    if(!is_in_alphabet(tape_alphabet, q[2])) {
      tape_alphabet.push_back(q[2]);
    }
  }

  for(auto &q : m) {
    if(q[3] == "l" && q[4] != "halt-accept") {
      // TODO
    }
  }

  // coloca o resto de m em m_new
  for(auto &q : m) {
    // insere a quintupla apenas se esta nao estiver marcada
    if(q.size() == 5) m_new.push_back(q);
  }

  return m_new;
}

#endif