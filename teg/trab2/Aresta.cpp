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

Aresta::Aresta(Vertice* const v1, Vertice* const v2, int weight):
                                v1{v1}, v2{v2}, weight{weight}{}

Aresta::~Aresta(){}

Vertice* Aresta::getVertice1() const{
	return v1;
}

Vertice* Aresta::getVertice2() const{
	return v2;
}

float Aresta::getWeight() const{
    return this->weight;
}