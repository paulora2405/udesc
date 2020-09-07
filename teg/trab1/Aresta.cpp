#include "Aresta.hpp"
#include "Vertice.hpp"
#include <iostream>
#include <cmath>

Aresta::Aresta(Vertice* const v1, Vertice* const v2):v1{v1}, v2{v2}{
    this->weight = sqrt( pow((v1->getX() - v2->getX()), 2) + pow((v1->getY() - v2->getY()), 2) );
	//podemos ainda verificar se v1 ou v2 são nulos
	//std::cout << "Criada aresta " << v1->getId() << "->" << v2->getId() << std::endl; 
}

Aresta::~Aresta(){
	//std::cout << "Destruida aresta " << v1->getId() << "->" << v2->getId() << std::endl; 
}

Vertice* Aresta::getVertice1() const{
	return v1;
}

Vertice* Aresta::getVertice2() const{
	return v2;
}

float Aresta::getWeight() const{
    return this->weight;
}