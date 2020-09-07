#include <iostream>
#include "Vertice.hpp"
#include "Aresta.hpp"
#include "Grafo.hpp"

int n = 300;

int main(){
	Grafo* g{new Grafo(n)};

	std::cout << "Imprimindo grafo completo" << std::endl;
	g->imprimirGrafo();

	g->iniciaDFS();
	std::cout << "FIM" << std::endl;

	delete g;

}