#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <list>

#include "Aresta.hpp"

class Vertice{
	friend class Grafo;
	public:
		unsigned int getId() const;
        float getX() const;
        float getY() const;
		Aresta* adicionarAresta(Vertice* const v2);
		void removerAresta(Aresta* a);
		void imprimirLigacoes() const;
	private:
		Vertice(float x, float y);
		~Vertice();

		void adicionarAresta(const Aresta* const aresta);

		static unsigned int proxId;
		unsigned int id;
        float x;
        float y;
		std::list<const Aresta*> arestas;
};
#endif