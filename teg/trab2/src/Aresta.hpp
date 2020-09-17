/**
    BCC-20 TEG : Header da classe Aresta
    @file Aresta.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20
*/
#ifndef ARESTA_HPP
#define ARESTA_HPP

class Vertice;

class Aresta {
  friend class Vertice;
  //-----------------------------public------------------------------//
public:
  /**
   * Retorna um ponteiro para o vertice de origem.
   * @returns Ponteiro para o vertice de origem.
   */
  Vertice* getVertice1() const;

  /**
   * Retorna um ponteiro para o vertice de destino.
   * @returns Ponteiro para o vertice de destino.
   */
  Vertice* getVertice2() const;

  /**
   * Retorna o peso da aresta.
   * @returns Peso da aresta.
   */
  float getWeight() const;
  //------------------------------private-----------------------------//
private:
  /**
   * Define vertices de origem e destino e o
   * 	peso da aresta (distancia entre vertices).
   * @param[in] v1 Vertice origem.
   * @param[in] v2 Vertice destino.
   * @param[in] weight Peso da aresta.
   */
  Aresta(Vertice* const v1, Vertice* const v2, int weight);

  /**
   * Deleta a aresta.
   */
  ~Aresta();

  /// Vertice de origem.
  Vertice* const v1;

  /// Vertice de destino.
  Vertice* const v2;

  /// Peso da aresta (Distancia entre origem e destino).
  int weight;
};
#endif