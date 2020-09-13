/**
    BCC-20 TEG : Implementacao da classe Grafo
    @file Grafo.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20 
*/
#include "Grafo.hpp"

Grafo::Grafo() : vertices(new std::list<Vertice*>) {
  this->criaGrafoGn();
}

Grafo::~Grafo() {
  std::list<Vertice*>::iterator it = this->vertices->begin();
  for(; it != this->vertices->end(); it++) {
    delete *it;
  }
  delete vertices;
}

void Grafo::criaGrafoGn() {
  this->adicionarVertice("Joinville");
  this->adicionarVertice("Florianopolis");
  this->adicionarVertice("Blumenal");
  this->adicionarVertice("São José");
  this->adicionarVertice("Chapecó");
  this->adicionarVertice("Itajaí");
  this->adicionarVertice("Criciúma");
  this->adicionarVertice("Jaraguá do Sul");
  this->adicionarVertice("Palhoça");
  this->adicionarVertice("Lages");

  //Id cidade origem, Id cidade destino, distancia entre as cidades

  //Joinville

  this->adicionarAresta(0, 1, 182);
  this->adicionarAresta(0, 2, 104);
  this->adicionarAresta(0, 3, 176);
  this->adicionarAresta(0, 4, 512);
  this->adicionarAresta(0, 5, 93);
  this->adicionarAresta(0, 6, 366);
  this->adicionarAresta(0, 7, 46);
  this->adicionarAresta(0, 8, 180);
  this->adicionarAresta(0, 9, 312);

  //Florianopolis
  this->adicionarAresta(1, 2, 148);
  this->adicionarAresta(1, 3, 10);
  this->adicionarAresta(1, 4, 553);
  this->adicionarAresta(1, 5, 98);
  this->adicionarAresta(1, 6, 203);
  this->adicionarAresta(1, 7, 187);
  this->adicionarAresta(1, 8, 20);
  this->adicionarAresta(1, 9, 226);

  //Blumenau
  this->adicionarAresta(2, 3, 146);
  this->adicionarAresta(2, 4, 470);
  this->adicionarAresta(2, 5, 63);
  this->adicionarAresta(2, 6, 337);
  this->adicionarAresta(2, 7, 64);
  this->adicionarAresta(2, 8, 153);
  this->adicionarAresta(2, 9, 224);

  //Sao Jose
  this->adicionarAresta(3, 4, 477);
  this->adicionarAresta(3, 5, 62);
  this->adicionarAresta(3, 6, 337);
  this->adicionarAresta(3, 7, 60);
  this->adicionarAresta(3, 8, 153);
  this->adicionarAresta(3, 9, 223);

  //Chapeco
  this->adicionarAresta(4, 5, 530);
  this->adicionarAresta(4, 6, 509);
  this->adicionarAresta(4, 7, 487);
  this->adicionarAresta(4, 8, 534);
  this->adicionarAresta(4, 9, 331);

  //Itajai
  this->adicionarAresta(5, 6, 281);
  this->adicionarAresta(5, 7, 97);
  this->adicionarAresta(5, 8, 96);
  this->adicionarAresta(5, 9, 275);

  //Criciúma
  this->adicionarAresta(6, 7, 371);
  this->adicionarAresta(6, 8, 185);
  this->adicionarAresta(6, 9, 204);

  //Jaragua
  this->adicionarAresta(7, 8, 186);
  this->adicionarAresta(7, 9, 262);

  //Palhoca
  this->adicionarAresta(8, 9, 207);

  //Lages
  //Nao aparece pois todas as ligacoes ja foram feitas
}

void Grafo::construirArvore(std::string raiz) {
  std::list<Vertice*>::iterator it = this->vertices->begin();
  for(; it != this->vertices->end(); it++)
    if((*it)->getName() == raiz)
      break;

  int idRaiz = (*it)->getId();

  bool visitados[10];

  construirArvore(idRaiz, visitados, idRaiz);
}

int Grafo::construirArvore(int id, bool visitados[], int& idRaiz) {
  // std::cout << "Id:" << id << std::endl;
  int max = pow(2, this->vertices->back()->proxId - 1);  // == 512
  int soma = 0;
  visitados[id] = true;

  for(int i = 0; i < 10; i++) {
    if(!visitados[i]) {
      bool visitados_copy[10];
      for(int i = 0; i < 10; i++) {
        visitados_copy[i] = visitados[i];
      }

      soma += construirArvore(i, visitados_copy, idRaiz);
    }
  }
  return soma;
}

void Grafo::iniciaDFS() {
  int qntVertices = this->vertices->size();
  bool* visited = new bool[qntVertices];
  for(int i = 0; i < qntVertices; i++)
    visited[i] = false;

  std::list<int>* marcados = new std::list<int>;

  int id = rand() % qntVertices;  //raiz aleatória
  std::cout << std::endl
            << "Raiz=V" << id + 1 << std::endl
            << "Iniciando o DFS:" << std::endl;

  std::list<Vertice*>::iterator it = this->vertices->begin();  //aponta o iterador para a raiz
  while((*it)->id <= id)
    it++;
  // buscaProfundidade((*it), visited, marcados); //chama a primeira vez o DFS, passando a raiz

  std::cout << std::endl;
  delete visited;
  marcados->clear();
  delete marcados;
}

Vertice* Grafo::adicionarVertice(std::string name) {
  Vertice* v{new Vertice(name)};
  this->vertices->push_back(v);
  return v;
}

void Grafo::removerVertice(Vertice* v) {
  std::list<Vertice*>::iterator it = this->vertices->begin();

  for(; it != this->vertices->end() && (*it) != v; it++)
    ;

  if(it != this->vertices->end()) {
    vertices->erase(it);
    delete *it;
  }
}

Aresta* Grafo::adicionarAresta(std::string name1, std::string name2, int distancia) {
  if(distancia <= 0)  //nao aceitamos distancia negativa ou nula
    return nullptr;

  std::list<Vertice*>::const_iterator it = this->vertices->cbegin();
  Vertice* v1 = nullptr;
  Vertice* v2 = nullptr;

  for(; it != this->vertices->end(); it++) {
    if((*it)->getName() == name1) {
      v1 = (*it);
    } else if((*it)->getName() == name2) {
      v2 = (*it);
    }
  }
  if(v1 == nullptr || v2 == nullptr)  //verifica se algum dos dois nao encontra-se na lista
    return nullptr;

  return v1->adicionarAresta(v2, distancia);
}

Aresta* Grafo::adicionarAresta(int id1, int id2, int distancia) {
  if(distancia <= 0)  //nao aceitamos distancia negativa ou nula
    return nullptr;

  std::list<Vertice*>::const_iterator it = this->vertices->cbegin();
  Vertice* v1 = nullptr;
  Vertice* v2 = nullptr;

  for(; it != this->vertices->end(); it++) {
    if((*it)->getId() == id1) {
      v1 = (*it);
    } else if((*it)->getId() == id2) {
      v2 = (*it);
    }
  }
  if(v1 == nullptr || v2 == nullptr)  //verifica se algum dos dois nao encontra-se na lista
    return nullptr;

  return v1->adicionarAresta(v2, distancia);
}

Aresta* Grafo::adicionarAresta(Vertice* const v1, Vertice* const v2, int distancia) {
  return v1->adicionarAresta(v2, distancia);
}

void Grafo::removerAresta(Aresta* a) {
  Vertice* v1{a->getVertice1()};
  v1->removerAresta(a);
}

void Grafo::imprimirGrafo() const {
  std::list<Vertice*>::const_iterator it = this->vertices->begin();
  for(; it != this->vertices->end(); it++) {
    // std::cout << "Vertice V" << (*it)->getId() << "(" << (*it)->getX() << ")(" << (*it)->getY() << ")" << "\t Ligacoes: "; //imprime com a pos x e y
    std::cout << "Vertice " << (*it)->getName() << "\t Ligacoes: ";  //imprime sem a pos x e y
    (*it)->imprimirLigacoes();
  }
}

const std::list<Vertice*>* Grafo::getVertices() const {
  return vertices;
}