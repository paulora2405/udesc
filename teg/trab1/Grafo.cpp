#include "Grafo.hpp"

Grafo::Grafo(int n) : vertices(new std::list<Vertice*>), n{n}{
	srand(time(NULL));
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

	int k = (int) floor(log2(this->n));
	
	typedef struct{
		Vertice* v;
		float d;
	}Vizinho;

	for(int i=0; i<this->n; i++)
		this->adicionarVertice();

	std::list<Vertice*>::const_iterator it = this->vertices->cbegin();
	while(it != this->vertices->end()){
		std::list<Vertice*>::const_iterator it_vizinho = this->vertices->cbegin();
		
		std::list<Vizinho> vizinhos;
		vizinhos.push_front(Vizinho{NULL, 10});

		while(it_vizinho != this->vertices->end()){

			if(it != it_vizinho){
				float dis = calculaDistancia((*it), (*it_vizinho));

				std::list<Vizinho>::iterator it_v = vizinhos.begin();

				for(int h=0; h<k; h++){
					if(dis < (*it_v).d){
							
						vizinhos.insert(it_v, Vizinho{(*it_vizinho), dis});

						if(vizinhos.size() > k)
							vizinhos.pop_back();
						break;
					}
					it_v++;
				}
			}
			it_vizinho++;
		}
		std::list<Vizinho>::iterator it_v = vizinhos.begin();
		while(it_v != vizinhos.end() && (*it)->arestas.size() < k && (*it_v).v->arestas.size() < k){
			this->adicionarAresta((*it), (*it_v).v);
			it_v++;
		}
		it++;
	}
}

float Grafo::calculaDistancia(Vertice* const v1, Vertice* const v2){
	return sqrt( pow((v1->getX() - v2->getX()), 2) + pow((v1->getY() - v2->getY()), 2) );
}

void Grafo::iniciaDFS(){
	bool *visited = new bool[this->n];
	for(int i=0; i<this->n; i++)
		visited[i] = false;
	
	std::list<int>* marcados = new std::list<int>;

	int id = rand() % this->n; //raiz aleatória
	std::cout << std::endl << "Raiz=V" << id+1 << std::endl << "Iniciando o DFS:" << std::endl;

	std::list<Vertice*>::iterator it = this->vertices->begin(); //aponta o iterador para a raiz
	while((*it)->id <= id)
		it++;
	buscaProfundidade((*it), visited, marcados); //chama a primeira vez o DFS, passando a raiz

	std::cout << std::endl;
	delete visited;
	marcados->clear();
	delete marcados;
}

void Grafo::buscaProfundidade(Vertice* v, bool visited[], std::list<int>* marcados){ //funcao privada que só pode ser chamada de dentro da instancia da classe
	std::cout << std::endl;
	visited[v->id] = true;

	marcados->push_back(v->id); //para sabermos a ordem de construcao da ordem
	
	std::list<int>::iterator itm = marcados->begin();
	while(itm != marcados->end())
		std::cout << "V" << (*itm++) << " ";
	std::cout << std::endl;
	
	std::list<const Aresta* >::iterator it;
	for(it = v->arestas.begin(); it != v->arestas.end(); it++){
		Vertice* viz = (*it)->getVertice2(); //proximo vertice alcancado (vizinho)
		if(viz == v)
			viz = (*it)->getVertice1();
		if(!visited[viz->id]){ //se o vizinho ainda nao foi visitado, chamamos recursivamente a busca em profundidade
			buscaProfundidade(viz, visited, marcados);
			std::cout << "V" << viz->id << "| "; //para visualizacao do backtracking
		}
	}
	//std::cout << std::endl;
}

Vertice* Grafo::adicionarVertice(){
	float x, y;
	x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	Vertice* v{new Vertice(x, y)};
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

Aresta* Grafo::adicionarAresta(Vertice* const v1, Vertice* const v2){
	return v1->adicionarAresta(v2);
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