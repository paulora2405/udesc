/**
    BCC-20 TEG : Header da classe Aresta
    @file Aresta.hpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#ifndef ARESTA_HPP
#define ARESTA_HPP

class Vertice;

class Aresta{
	friend class Vertice;
	public:
		Vertice* getVertice1() const;
		Vertice* getVertice2() const;
        float getWeight() const;
	private:
		Aresta(Vertice* const v1, Vertice* const v2, int weight);
		~Aresta();

		Vertice* const v1;
		Vertice* const v2;
		int weight;
};
#endif