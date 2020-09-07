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
		Aresta(Vertice* const v1, Vertice* const v2);
		~Aresta();

		Vertice* const v1;
		Vertice* const v2;
		float weight;
};
#endif