/**
    BCC-20 TEG : Implementacao da classe Grafo
    @file Grafo.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include "Grafo.hpp"


/**
 * Inicializa a lista de vertices.
*/
Grafo::Grafo(): vertices(new std::list<Vertice*>){
	this->criaGrafoGn();
}

/**
 * Deleta todos os vertices da lista de vertices, e, em seguida, deleta o grafo.
*/
Grafo::~Grafo(){
	std::list<Vertice*>::iterator it = this->vertices->begin();
	for( ;it != this->vertices->end(); it++){
		delete *it;
	}
	delete vertices;
}

/**
 * Cria grafo completo com todas as cidades, e as arestas entre cada uma delas, com suas respectivas distancias.
*/
void Grafo::criaGrafoGn(){
	
	this->adicionarVertice("Florianopolis"); //repetir para todas

	// TODO: adicionar arestas
	
}

/**
 * Inicia o algoritomo de busca em profundidade.
*/
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

/**
 * Adiciona um vertice a lista de vertices do grafo de chamada.
 * @param[in] name Nome do vertice a ser adicionado.
 * @returns Ponteiro para vertice adicionado.
*/
Vertice* Grafo::adicionarVertice(std::string name){
	Vertice* v{new Vertice(name)};
	this->vertices->push_back(v);
	return v;
}

/**
 * Remove um vertice da lista de vertices do grafo de chamada, e o deleta.
 * @param[in] v Vertice a ser removido
*/
void Grafo::removerVertice(Vertice* v){
	std::list<Vertice*>::iterator it = this->vertices->begin();
	
	for( ;it != this->vertices->end() && (*it) != v; it++);

	if(it != this->vertices->end()){
		vertices->erase(it);
		delete *it;
	}
}

/**
 * Adiciona uma aresta entre dois vertices com os nomes 1 e 2 e define sua distancia.
 * @param[in] name1 Nome do vertice de origem.
 * @param[in] name2 Nome do vertice de destino.
 * @param[in] distancia Distancia entre os dois vertices.
 * @returns Ponteiro para a aresta criada, ou nullptr se a distancia for <= 0, ou
 * 		nullptr se algum dos dois nomes nao correspomderem a nenhum vertice da
 * 		lista de vertices do grafo de chamada.
*/
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

/**
 * Adiciona uma aresta entre dois vertices v1 e v2 e define sua distancia.
 * @param[in] v1 Vertice de origem.
 * @param[in] v2 Vertice de destino.
 * @param[in] distancia Distancia entre os dois vertices.
 * @returns Ponteiro para a aresta criada.
*/
Aresta* Grafo::adicionarAresta(Vertice* const v1, Vertice* const v2, int distancia){
	return v1->adicionarAresta(v2, distancia);
}

/**
 * Remove uma aresta tanto da origem como do destino.
 * @param[in] a Aresta a ser removida.
*/
void Grafo::removerAresta(Aresta* a){
	Vertice* v1{a->getVertice1()};
	v1->removerAresta(a);
}

/**
 * Imprime todas as ligacoes de todos os vertices do grafo.
*/
void Grafo::imprimirGrafo() const{
	std::list<Vertice*>::const_iterator it = this->vertices->begin();
	for( ;it != this->vertices->end(); it++){
		// std::cout << "Vertice V" << (*it)->getId() << "(" << (*it)->getX() << ")(" << (*it)->getY() << ")" << "\t Ligacoes: "; //imprime com a pos x e y
		std::cout << "Vertice V" << (*it)->getId() << "\t Ligacoes: "; //imprime sem a pos x e y
		(*it)->imprimirLigacoes();
	}
}

/**
 * Retorna a lista de vertices do grafo de chamada.
 * @returns Lista de vertices.
*/
const std::list<Vertice*>* Grafo::getVertices() const{
	return vertices;
}