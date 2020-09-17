/**
    BCC-20 TEG : Header da classe Grafo
    @file Grafo.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20
*/
#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <cmath>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <list>

#include "Aresta.hpp"
#include "Vertice.hpp"

class Grafo {
  //-----------------------------public------------------------------//
public:
  /// Inicializa a lista de vertices.
  Grafo();

  /**
   * Deleta todos os vertices da lista de vertices, e,
   * 	em seguida, deleta o grafo.
   */
  ~Grafo();

  /**
   * Executa os algoritmos de construção das arvores, mínimos sucessivos e o outro la.
   */
  void algoritmos();

  //------------------------------private-----------------------------//
private:
  /**
   * Começa a contrução da árvore a partir da raiz.
   * @param[in] raiz Nome da cidade raiz do algoritmo.
   */
  void construirArvore(std::string raiz);

  /**
   * Começa o algoritmo dos minimos sucessivos a partir da raiz.
   * @param[in] id Id da cidade raiz.
   */
  void minimosSucessivos(int id);

  /// Imprime todas as ligacoes de todos os vertices do grafo de chamada.
  void imprimirGrafo() const;

  /**
   * Cria grafo completo com todas as cidades, e as arestas
   * 	entre cada uma delas, com suas respectivas distancias.
   */
  void criaGrafoGn();

  /**
   * RECURSIVA - Construcao recursiva da arvore.
   * @param[in] v Vertice atual.
   * @param[in] visited Vetor booleano de vertices visitados.
   * @param[in] marcados Lista encadeada dos ids visitados na ordem de visita.
   */
  void construirArvore(Vertice *v, bool visited[], std::list<int> *marcados);

  /**
   * RECURSIVA - Algoritmo recursivo dos minimos sucessivos.
   * @param[in] id Id do vertice atual.
   * @param[in] soma Soma do caminho atual.
   */
  void minimosSucessivos(int id, bool visited[], std::list<int> *marcados);

  /**
   * Adiciona um vertice a lista de vertices do grafo de chamada.
   * @param[in] name Nome do vertice a ser adicionado.
   * @returns Ponteiro para vertice adicionado.
   */
  Vertice *adicionarVertice(std::string name);

  /**
   * Remove um vertice da lista de vertices do grafo de chamada, e o deleta.
   * @param[in] v Vertice a ser removido
   */
  void removerVertice(Vertice *v);

  /**
   * Adiciona uma aresta entre dois vertices com os nomes 1 e 2
   * 	e define sua distancia.
   * @param[in] name1 Nome do vertice de origem.
   * @param[in] name2 Nome do vertice de destino.
   * @param[in] distancia Distancia entre os dois vertices.
   * @returns Ponteiro para a aresta criada,
   * 	ou nullptr se a distancia for <= 0, ou
   * 	nullptr se algum dos dois nomes nao correspomderem a nenhum
   * 	vertice da lista de vertices do grafo de chamada.
   */
  Aresta *adicionarAresta(std::string name1, std::string name2, int distancia);

  /**
   * Adiciona uma aresta entre dois vertices com os id's 1 e 2
   * 	e define sua distancia.
   * @param[in] id1 Id do vertice de origem.
   * @param[in] id2 Id do vertice de destino.
   * @returns Ponteiro para a aresta criada,
   * 	ou nullptr se a distancia for <= 0, ou
   * 	nullptr se algum dos dois nomes nao correspomderem a nenhum
   * 	vertice da lista de vertices do grafo de chamada.
   */
  Aresta *adicionarAresta(int id1, int id2, int distancia);

  /**
   * Adiciona uma aresta entre dois vertices v1 e v2 e define sua distancia.
   * @param[in] v1 Vertice de origem.
   * @param[in] v2 Vertice de destino.
   * @param[in] distancia Distancia entre os dois vertices.
   * @returns Ponteiro para a aresta criada.
   */
  Aresta *adicionarAresta(Vertice *const v1, Vertice *const v2, int distancia);

  /**
   * Remove uma aresta tanto da origem como do destino.
   * @param[in] a Aresta a ser removida.
   */
  void removerAresta(Aresta *a);

  /**
   * Retorna a lista de vertices do grafo de chamada.
   * @returns Lista de vertices.
   */
  const std::list<Vertice *> *getVertices() const;

  /// Lista de ponteiros para os vertices do grafo.
  std::list<Vertice *> *vertices;

  std::list<std::string> ca_CaminhoMin;
  int ca_SomaMin;
  int soma;
  int caminhou;
};
#endif