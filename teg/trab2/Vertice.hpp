/**
    BCC-20 TEG : Header da classe Vertice
    @file Vertice.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#ifndef VERTICE_HPP
#define VERTICE_HPP

#include "Aresta.hpp"
#include <list>
#include <string>

class Vertice{
	friend class Grafo;
	public:
		unsigned int getId() const;
		std::string getName() const;
		Aresta* adicionarAresta(Vertice* const v2, int distancia);
		void removerAresta(Aresta* a);
		void imprimirLigacoes() const;

	private:
		Vertice(std::string name);
		~Vertice();

		void adicionarAresta(const Aresta* const aresta);

		static unsigned int proxId;
		unsigned int id;
        std::string name;
		std::list<const Aresta*> arestas;
};
#endif