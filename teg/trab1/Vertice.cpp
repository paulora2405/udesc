#include "Vertice.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

unsigned int Vertice::proxId{0};

Vertice::Vertice(float x, float y) : id{proxId}, x{x}, y{y}{
	Vertice::proxId++;
}

Vertice::~Vertice(){
	//copiando a lista original para não corromper o iterador
	std::list<const Aresta*> copia = arestas;
	std::list<const Aresta*>::const_iterator it = copia.begin();
	Vertice* outro;
	for( ; it != copia.end(); it++){
		outro = (*it)->getVertice2();
		if(outro == this)
			outro = (*it)->getVertice1();
		outro->arestas.remove(*it);
		delete *it;
	}
	//std::cout << "Destruido Vertice V" << id << std::endl;

}

unsigned int Vertice::getId() const{
	return this->id;
}

float Vertice::getX() const{
    return this->x;
}

float Vertice::getY() const{
    return this->y;
}

Aresta* Vertice::adicionarAresta(Vertice* const v2){
	if(v2 == this)
		return nullptr; //não aceitamos arestas em que os dois vértices são o mesmos
	//verificando se ligação já existe
	std::list<const Aresta*>::const_iterator it = arestas.begin();
	for( ;it != arestas.end(); it++){
		if((*it)->getVertice1() == this && (*it)->getVertice2() == v2)
			return nullptr;
		if((*it)->getVertice1() == v2 && (*it)->getVertice2() == this)
			return nullptr;
	}
	
	Aresta* a{new Aresta{this,v2}};
	this->adicionarAresta(a);//chama a função de mesmo nome sobrecarregada
	v2->adicionarAresta(a);//adiciona a aresta no outro vértice
	
	return a;
}

void Vertice::adicionarAresta(const Aresta* const aresta){
	this->arestas.push_back(aresta);
}

void Vertice::removerAresta(Aresta* a){
	if(a->getVertice1() != this && a->getVertice2() != this){
		//tentando remover uma aresta que não contem esse vertice
		std::cerr<< "A aresta nao se relaciona com esse vertice"<< std::endl;
		return;
	}
	//podemos acessar arestas diretamente aqui, apesar de ser privado (mas pertence a classe Vertice)
	a->getVertice1()->arestas.remove(a);
	if(a->getVertice1() != a->getVertice2())
		a->getVertice2()->arestas.remove(a);

	delete a;
}

void Vertice::imprimirLigacoes() const{
	std::list<const Aresta*>::const_iterator it = arestas.begin();
	const Vertice* outro;
	for( ;it != arestas.end(); it++){
		std::cout << "V" << this->id << "->";
		outro = (*it)->getVertice2();
		//float peso;
		if(outro == this)
			outro = (*it)->getVertice1();
		// peso = (*it)->weight;
		// std::cout << "V" << outro->getId() << "(" << peso << ")" << "\t"; //imprime com a distancia
		std::cout << "V" << outro->getId() << " \t"; //imprime sem a distancia
	}
	std::cout << std::endl;

}