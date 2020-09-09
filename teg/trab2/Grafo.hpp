/**
    BCC-20 TEG : Header da classe Grafo
    @file Grafo.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <list>
#include <forward_list>
#include <iostream>
#include <cmath>
#include "Vertice.hpp"
#include "Aresta.hpp"

class Grafo{
	public:
		Grafo();
		~Grafo();
		void iniciaDFS();
		void imprimirGrafo() const;

	private:
		void criaGrafoGn();
		
		Vertice* adicionarVertice(std::string name);
		void removerVertice(Vertice* v);
		Aresta* adicionarAresta(std::string name1, std::string name2, int distancia);
		Aresta* adicionarAresta(Vertice* const v1, Vertice* const v2, int distancia);
		void removerAresta(Aresta* a);
		const std::list<Vertice*>* getVertices() const;
		
		std::list<Vertice*>* vertices;
};
#endif