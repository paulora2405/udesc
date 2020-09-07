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
		Grafo(int n);
		~Grafo();
		void iniciaDFS();
		void imprimirGrafo() const;

	private:
		void criaGrafoGn();
		float calculaDistancia(Vertice* const v1, Vertice* const v2);
		void buscaProfundidade(Vertice* v, bool visited[], std::list<int>* marcados);

		Vertice* adicionarVertice();
		void removerVertice(Vertice* v);
		Aresta* adicionarAresta(Vertice* const v1, Vertice* const v2);
		void removerAresta(Aresta* a);
		const std::list<Vertice*>* getVertices() const;
		
		const int n;
		std::list<Vertice*>* vertices;
};
#endif