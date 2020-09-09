/**
    BCC-20 TEG : Implementacao da classe Vertice
    @file Vertice.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include "Vertice.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

unsigned int Vertice::proxId{0};

/**
 * Define o nome e o id do vertice.
 * @param[in] name Nome do vertice.
*/
Vertice::Vertice(std::string name):id{proxId}, name{name}{
	Vertice::proxId++;
}

/**
 * Deleta todas as arestas na lista de arestas do vertice.
*/
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

/**
 * Retorna o id do vertice de chamada.
 * @returns Id do vertice.
*/
unsigned int Vertice::getId() const{
	return this->id;
}

/**
 * Retorna o nome do vertice de chamada.
 * @returns Nome do vertice.
*/
std::string Vertice::getName() const{
    return this->name;
}

/**
 * Adiciona uma aresta entre os vertices v1 e v2 com peso igual a distancia.
 * @param[in] v2 Vertice destino.
 * @param[in] distancia Distancia entre origem e destino.
 * @returns Ponteiro para a aresta criada, ou nullptr se v1 == v2, ou nullptr se a ligacao ja existir.
*/
Aresta* Vertice::adicionarAresta(Vertice* const v2, int distancia){
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
	
	Aresta* a{new Aresta{this,v2, distancia}};
	this->adicionarAresta(a);//chama a função de mesmo nome sobrecarregada
	v2->adicionarAresta(a);//adiciona a aresta no outro vértice
	
	return a;
}

/**
 * Adiciona uma aresta a lista de arestas de chamada.
 * @param[in] aresta Nova aresta.
*/
void Vertice::adicionarAresta(const Aresta* const aresta){
	this->arestas.push_back(aresta);
}

/**
 * Remove uma aresta das listas de arestas de sua origem e destino, e ,em seguida, deleta a instancia de aresta.
 * @param[in] a Aresta a ser removida.
*/
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

/**
 * Imprime as ligacoes do vertice de chamada.
*/
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