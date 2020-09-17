/**
    BCC-20 TEG : Header da classe Vertice
    @file Vertice.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20
*/
#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <list>
#include <string>

#include "Aresta.hpp"

class Vertice {
  friend class Grafo;
  //-----------------------------public------------------------------//
public:
  /**
   * Retorna o id do vertice de chamada.
   * @returns Id do vertice.
   */
  int getId() const;

  /**
   * Retorna o nome do vertice de chamada.
   * @returns Nome do vertice.
   */
  std::string getName() const;

  /**
   * Adiciona uma aresta entre o vertice de chamada e v2 com
   * 	peso igual a distancia.
   * @param[in] v2 Vertice destino.
   * @param[in] distancia Distancia entre origem e destino.
   * @returns Ponteiro para a aresta criada, ou nullptr se v1 == v2,
   * 		ou nullptr se a ligacao ja existir.
   */
  Aresta *adicionarAresta(Vertice *const v2, int distancia);

  /**
   * Remove uma aresta das listas de arestas de sua origem e destino, e,
   * 	em seguida, deleta a instancia de aresta.
   * @param[in] a Aresta a ser removida.
   */
  void removerAresta(Aresta *a);

  /**
   * Imprime as ligacoes do vertice de chamada.
   */
  void imprimirLigacoes() const;

  //------------------------------private-----------------------------//
private:
  /**
   * Define o nome e o id do vertice.
   * @param[in] name Nome do vertice.
   */
  Vertice(std::string name);

  /**
   * Deleta todas as arestas na lista de arestas do vertice.
   */
  ~Vertice();

  /**
   * Adiciona uma aresta a lista de arestas de chamada.
   * @param[in] aresta Nova aresta.
   */
  void adicionarAresta(const Aresta *const aresta);

  /**
   * Retorna a aresta correspondente
   */
  Aresta *procuraAresta(int id);

  /// Variavel statica da classe para controle de Id's.
  static unsigned int proxId;

  /// Id da instancia da classe Vertice.
  unsigned int id;

  /// Nome do vertice.
  std::string name;

  /// Lista de ponteiros para arestas do vertice.
  std::list<const Aresta *> arestas;
};
#endif