/**
    BCC-20 TEG : Implementacao da classe Grafo
    @file Grafo.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include "Grafo.hpp"


Grafo::Grafo(): vertices(new std::list<Vertice*>){
	this->criaGrafoGn();
}

Grafo::~Grafo(){
	std::list<Vertice*>::iterator it = this->vertices->begin();
	for( ;it != this->vertices->end(); it++){
		delete *it;
	}
	delete vertices;
}

void Grafo::criaGrafoGn(){
	
	this->adicionarVertice("Florianopolis"); //repetir para todas

	// TODO: adicionar arestas
	
}

void Grafo::iniciaDFS(){
	int qntVertices = this->vertices->size();
	bool *visited = new bool[qntVertices];
	for(int i=0; i<qntVertices; i++)
		visited[i] = false;
	
	std::list<int>* marcados = new std::list<int>;

	int id = rand() % qntVertices; //raiz aleatória
	std::cout << std::endl << "Raiz=V" << id+1 << std::endl << "Iniciando o DFS:" << std::endl;

	std::list<Vertice*>::iterator it = this->vertices->begin(); //aponta o iterador para a raiz
	while((*it)->id <= id)
		it++;
	// buscaProfundidade((*it), visited, marcados); //chama a primeira vez o DFS, passando a raiz

	std::cout << std::endl;
	delete visited;
	marcados->clear();
	delete marcados;
}

Vertice* Grafo::adicionarVertice(std::string name){
	Vertice* v{new Vertice(name)};
	this->vertices->push_back(v);
	return v;
}

void Grafo::removerVertice(Vertice* v){
	std::list<Vertice*>::iterator it = this->vertices->begin();
	
	for( ;it != this->vertices->end() && (*it) != v; it++);

	if(it != this->vertices->end()){
		vertices->erase(it);
		delete *it;
	}
}

Aresta* Grafo::adicionarAresta(std::string name1, std::string name2, int distancia){
	if(distancia <= 0) //nao aceitamos distancia negativa ou nula
		return nullptr;
	
	std::list<Vertice*>::const_iterator it = this->vertices->cbegin();
	Vertice* v1 = nullptr;
	Vertice* v2 = nullptr;
	
	for(; it!= this->vertices->end(); it++){
		if((*it)->getName() == name1){
			v1 = (*it);
		}
		else if((*it)->getName() == name2){
			v2 = (*it);
		}
	}
	if(v1==nullptr || v2== nullptr) //verifica se algum dos dois nao encontra-se na lista
		return nullptr;

	return v1->adicionarAresta(v2, distancia);
}

Aresta* Grafo::adicionarAresta(Vertice* const v1, Vertice* const v2, int distancia){
	return v1->adicionarAresta(v2, distancia);
}

void Grafo::removerAresta(Aresta* a){
	Vertice* v1{a->getVertice1()};
	v1->removerAresta(a);
}

void Grafo::imprimirGrafo() const{
	std::list<Vertice*>::const_iterator it = this->vertices->begin();
	for( ;it != this->vertices->end(); it++){
		// std::cout << "Vertice V" << (*it)->getId() << "(" << (*it)->getX() << ")(" << (*it)->getY() << ")" << "\t Ligacoes: "; //imprime com a pos x e y
		std::cout << "Vertice V" << (*it)->getId() << "\t Ligacoes: "; //imprime sem a pos x e y
		(*it)->imprimirLigacoes();
	}
}

const std::list<Vertice*>* Grafo::getVertices() const{
	return vertices;
}