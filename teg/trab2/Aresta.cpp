/**
    BCC-20 TEG : Implementacao da classe Aresta
    @file Aresta.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include "Aresta.hpp"
#include "Vertice.hpp"
#include <iostream>
#include <cmath>

/**
 * Define vertices de origem e destino e o peso da aresta (distancia entre vertices).
 * @param[in] v1 Vertice origem.
 * @param[in] v2 Vertice destino.
 * @param[in] weight Peso da aresta.
*/
Aresta::Aresta(Vertice* const v1, Vertice* const v2, int weight):v1{v1}, v2{v2}, weight{weight}{}

/**
 * Deleta a aresta.
*/
Aresta::~Aresta(){}

/**
 * Retorna um ponteiro para o vertice de origem.
 * @returns Ponteiro para o vertice de origem.
*/
Vertice* Aresta::getVertice1() const{
	return v1;
}

/**
 * Retorna um ponteiro para o vertice de destino.
 * @returns Ponteiro para o vertice de destino.
*/
Vertice* Aresta::getVertice2() const{
	return v2;
}

/**
 * Retorna o peso da aresta.
 * @returns Peso da aresta.
*/
float Aresta::getWeight() const{
    return this->weight;
}