/**
    BCC-20 TEG : Main
    @file main.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include <iostream>
#include "Vertice.hpp"
#include "Aresta.hpp"
#include "Grafo.hpp"

int main(){
	Grafo* g{new Grafo()};

	std::cout << "Imprimindo grafo completo" << std::endl;
	g->imprimirGrafo();

	g->iniciaDFS();
	std::cout << "FIM" << std::endl;

	delete g;

}