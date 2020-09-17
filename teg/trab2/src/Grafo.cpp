/**
    BCC-20 TEG : Implementacao da classe Grafo
    @file Grafo.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20
*/
#include "Grafo.hpp"

Grafo::Grafo() : vertices(new std::list<Vertice*>), ca_SomaMin{2147483647}, soma{0}, caminhou{0} {
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
  ///---------------------------------------
  // this->adicionarAresta(0, 1, 1);
  // this->adicionarAresta(0, 2, 2);
  // this->adicionarAresta(0, 3, 4);

  // this->adicionarAresta(1, 2, 8);
  // this->adicionarAresta(1, 3, 16);

  // this->adicionarAresta(2, 3, 32);
  ///---------------------------------------
  this->adicionarVertice("Chapecó");
  this->adicionarVertice("Itajaí");
  this->adicionarVertice("Criciúma");
  this->adicionarVertice("Jaraguá do Sul");
  this->adicionarVertice("Palhoça");
  this->adicionarVertice("Lages");

  // Id cidade origem, Id cidade destino, distancia entre as cidades

  // Joinville

  this->adicionarAresta(0, 1, 182);
  this->adicionarAresta(0, 2, 104);
  this->adicionarAresta(0, 3, 176);
  this->adicionarAresta(0, 4, 512);
  this->adicionarAresta(0, 5, 93);
  this->adicionarAresta(0, 6, 366);
  this->adicionarAresta(0, 7, 46);
  this->adicionarAresta(0, 8, 180);
  this->adicionarAresta(0, 9, 312);

  // Florianopolis
  this->adicionarAresta(1, 2, 148);
  this->adicionarAresta(1, 3, 10);
  this->adicionarAresta(1, 4, 553);
  this->adicionarAresta(1, 5, 98);
  this->adicionarAresta(1, 6, 203);
  this->adicionarAresta(1, 7, 187);
  this->adicionarAresta(1, 8, 20);
  this->adicionarAresta(1, 9, 226);

  // Blumenau
  this->adicionarAresta(2, 3, 146);
  this->adicionarAresta(2, 4, 470);
  this->adicionarAresta(2, 5, 63);
  this->adicionarAresta(2, 6, 337);
  this->adicionarAresta(2, 7, 64);
  this->adicionarAresta(2, 8, 153);  // AAAAA
  this->adicionarAresta(2, 9, 224);

  // Sao Jose
  this->adicionarAresta(3, 4, 477);
  this->adicionarAresta(3, 5, 62);
  this->adicionarAresta(3, 6, 337);
  this->adicionarAresta(3, 7, 60);
  this->adicionarAresta(3, 8, 153);  // AAAAA
  this->adicionarAresta(3, 9, 223);

  // Chapeco
  this->adicionarAresta(4, 5, 530);
  this->adicionarAresta(4, 6, 509);
  this->adicionarAresta(4, 7, 487);
  this->adicionarAresta(4, 8, 534);
  this->adicionarAresta(4, 9, 331);

  // Itajai
  this->adicionarAresta(5, 6, 281);
  this->adicionarAresta(5, 7, 97);
  this->adicionarAresta(5, 8, 96);
  this->adicionarAresta(5, 9, 275);

  // Criciúma
  this->adicionarAresta(6, 7, 371);
  this->adicionarAresta(6, 8, 185);
  this->adicionarAresta(6, 9, 204);

  // Jaragua
  this->adicionarAresta(7, 8, 186);
  this->adicionarAresta(7, 9, 262);

  // Palhoca
  this->adicionarAresta(8, 9, 207);

  // Lages
  // Nao aparece pois todas as ligacoes ja foram feitas
}

void Grafo::algoritmos() {
  // arvores
  this->construirArvore("Joinville");

  // minimos sucessivos
  for(int i = 0; i < (int)this->vertices->size(); i++) {
    this->minimosSucessivos(i);
  }
  std::ofstream file;
  file.open("minimos_sucessivos.txt");
  std::list<std::string>::const_iterator sit = ca_CaminhoMin.begin();
  while(sit != ca_CaminhoMin.end()) {
    file << (*sit) << std::endl;
    sit++;
  }
  file.close();

  ordenacaoPesoArestas();
}

void Grafo::ordenacaoPesoArestas() {
  std::list<MicroAresta> arestasOrdenadas;

  std::list<Vertice*>::const_iterator itVertices = this->vertices->cbegin();
  for(; itVertices != this->vertices->cend(); itVertices++) {
    std::list<const Aresta*>::const_iterator itArestas = (*itVertices)->arestas.cbegin();
    for(; itArestas != (*itVertices)->arestas.cend(); itArestas++) {
      int pesoAresta = (*itArestas)->getWeight();
      std::list<MicroAresta>::iterator itArestasOrd = arestasOrdenadas.begin();
      while(itArestasOrd != arestasOrdenadas.end() && (*itArestasOrd).peso < pesoAresta) {
        itArestasOrd++;
      }
      if(pesoAresta == (*itArestasOrd).peso) {
        // std::cout << pesoAresta << " " << (*itArestasOrd).peso << std::endl;
        continue;
      }
      MicroAresta temp = {pesoAresta, (*itArestas)->getVertice1(), (*itArestas)->getVertice2()};
      arestasOrdenadas.insert(itArestasOrd, temp);
    }
  }

  // std::list<MicroAresta>::const_iterator itArestasOrd = arestasOrdenadas.cbegin();
  // for(; itArestasOrd != arestasOrdenadas.cend(); itArestasOrd++) {
  //   std::cout << (*itArestasOrd).v1->getId() << "->" << (*itArestasOrd).v2->getId()
  //             << " S:" << (*itArestasOrd).peso << std::endl;
  // }

  int nArestasNoVertice[(int)this->vertices->size()] = {};
  std::list<MicroAresta> arestasMenorPeso;

  std::list<MicroAresta>::const_iterator itArestasOrd = arestasOrdenadas.cbegin();
  for(; itArestasOrd != arestasOrdenadas.cend(); itArestasOrd++) {
    if(nArestasNoVertice[(*itArestasOrd).v1->getId()] < 2 &&
       nArestasNoVertice[(*itArestasOrd).v2->getId()] < 2 &&
       (!ehCiclico((*itArestasOrd).v1->getId(), (*itArestasOrd).v2->getId(), arestasMenorPeso) ||
        arestasMenorPeso.size() == this->vertices->size() - 1)) {
      arestasMenorPeso.push_back((*itArestasOrd));
      nArestasNoVertice[(*itArestasOrd).v1->getId()]++;
      nArestasNoVertice[(*itArestasOrd).v2->getId()]++;
    }
  }
  // para printar
  // std::list<MicroAresta>::const_iterator itArestasMenorPeso = arestasMenorPeso.cbegin();
  // for(; itArestasMenorPeso != arestasMenorPeso.cend(); itArestasMenorPeso++) {
  //   std::cout << (*itArestasMenorPeso).v1->getId() << "->" << (*itArestasMenorPeso).v2->getId()
  //             << "\tS:" << (*itArestasMenorPeso).peso << std::endl;
  // }
}

bool Grafo::ehCiclico(int idOrig, int idDest, std::list<MicroAresta> arestasMenorPeso) {
  std::list<MicroAresta>::const_iterator itArestasMenorPeso = arestasMenorPeso.cbegin();
  if(itArestasMenorPeso == arestasMenorPeso.cend()) return false;

  while((*itArestasMenorPeso).v1->getId() != idDest &&
        (*itArestasMenorPeso).v2->getId() != idDest) {
    itArestasMenorPeso++;
    if(itArestasMenorPeso == arestasMenorPeso.end()) return false;
  }

  int outro;
  int ultimo;
  int avancou = 1;
  while(avancou == 1) {
    avancou = 0;
    itArestasMenorPeso = arestasMenorPeso.cbegin();
    for(; itArestasMenorPeso != arestasMenorPeso.cend(); itArestasMenorPeso++) {
      if(((*itArestasMenorPeso).v1->getId() == idDest ||
          (*itArestasMenorPeso).v2->getId() == idDest) &&
         ((*itArestasMenorPeso).v1->getId() != ultimo &&
          (*itArestasMenorPeso).v2->getId() != ultimo)) {
        outro = (*itArestasMenorPeso).v1->getId();
        if(outro == idDest) outro = (*itArestasMenorPeso).v2->getId();
        avancou = 1;
        if(outro == idOrig) return true;
      }
    }
    ultimo = idDest;
    idDest = outro;
  }
  return false;
}

void Grafo::minimosSucessivos(int id) {
  bool* visited = new bool[this->vertices->size()];
  std::list<int>* marcados = new std::list<int>;
  visited[id] = true;

  marcados->push_back(id);

  // raiz
  std::list<Vertice*>::iterator it = this->vertices->begin();
  while((*it)->getId() != id) {
    it++;
  }

  std::list<const Aresta*>::iterator aresIt = (*it)->arestas.begin();
  int min = 2147483647;
  const Vertice* outro;
  const Vertice* verMin;

  for(; aresIt != (*it)->arestas.end(); aresIt++) {
    outro = (*aresIt)->getVertice2();
    if(outro == (*it)) outro = (*aresIt)->getVertice1();
    // ok
    if(!visited[outro->getId()]) {
      if(min > (*aresIt)->getWeight()) {
        min = (*aresIt)->getWeight();
        verMin = outro;
      }
    }
  }
  // dps do for
  marcados->push_back(verMin->getId());
  this->soma = min;
  minimosSucessivos(verMin->getId(), visited, marcados);

  std::list<int>::const_iterator mit = marcados->cbegin();
  if(soma < ca_SomaMin) {
    ca_SomaMin = soma;
    ca_CaminhoMin.clear();
    std::string s = "";
    for(; mit != marcados->end(); mit++) s += std::to_string((*mit)) + ",";
    s += std::to_string(soma);
    ca_CaminhoMin.push_back(s);

  } else if(soma == ca_SomaMin) {
    std::string s = "";
    for(; mit != marcados->end(); mit++) s += std::to_string((*mit)) + ",";
    s += std::to_string(soma);
    ca_CaminhoMin.push_back(s);
  }

  // std::list<int>::const_iterator mit = marcados->cbegin();
  // for(; mit != marcados->cend(); mit++) { std::cout << (*mit) << ","; }
  // std::cout << soma << std::endl;
}

void Grafo::minimosSucessivos(int id, bool visited[], std::list<int>* marcados) {
  visited[id] = true;

  std::list<Vertice*>::iterator it = this->vertices->begin();
  while((*it)->getId() != id) {
    it++;
  }

  std::list<const Aresta*>::iterator aresIt = (*it)->arestas.begin();
  int min = 2147483647;
  const Vertice* outro;
  const Vertice* verMin;

  for(; aresIt != (*it)->arestas.end(); aresIt++) {
    outro = (*aresIt)->getVertice2();
    if(outro == (*it)) outro = (*aresIt)->getVertice1();

    if(!visited[outro->getId()]) {
      if(min > (*aresIt)->getWeight()) {
        min = (*aresIt)->getWeight();
        verMin = outro;
      }
    }
  }
  marcados->push_back(verMin->getId());
  this->soma += min;

  if(marcados->size() == this->vertices->size()) {
    std::list<const Aresta*>::const_iterator aresIt = verMin->arestas.begin();
    // int min = 2147483647;

    for(; aresIt != verMin->arestas.end(); aresIt++) {
      outro = (*aresIt)->getVertice2();
      if(outro == verMin) outro = (*aresIt)->getVertice1();

      if(outro->getId() == (int)marcados->front()) {
        soma += (*aresIt)->getWeight();
        marcados->push_back((int)marcados->front());
        return;
      }
    }
  }

  minimosSucessivos(verMin->getId(), visited, marcados);
}

void Grafo::construirArvore(std::string raiz) {
  bool* visited = new bool[this->vertices->size()];

  std::list<int>* marcados = new std::list<int>;

  std::list<Vertice*>::iterator it = this->vertices->begin();  // aponta o iterador para a raiz
  while((*it)->name != raiz) it++;

  construirArvore((*it), visited, marcados);  // chama a primeira vez, passando a raiz

  std::ofstream file;
  file.open("construcao_arvore.txt");
  std::list<std::string>::const_iterator sit = ca_CaminhoMin.begin();
  while(sit != ca_CaminhoMin.end()) {
    file << (*sit) << std::endl;
    sit++;
  }
  file.close();

  ca_SomaMin = 2147483647;
  ca_CaminhoMin.clear();
}

void Grafo::construirArvore(Vertice* v, bool visited[], std::list<int>* marcados) {
  int printado = 0;
  // int lista_cheia = 1;
  visited[v->id] = true;

  if(marcados->size() >= 1) {
    Aresta* a = v->procuraAresta(marcados->back());
    this->soma += a->getWeight();
  }
  marcados->push_back(v->id);

  std::list<Vertice*>::iterator it = this->vertices->begin();

  for(; it != this->vertices->end(); it++) {
    if((int)marcados->size() == (int)this->vertices->size() && printado == 0) {
      Aresta* a = v->procuraAresta(marcados->front());
      soma = soma + a->getWeight();
      std::list<int>::const_iterator mit = marcados->cbegin();

      if(soma < ca_SomaMin) {
        ca_SomaMin = soma;
        ca_CaminhoMin.clear();
        std::string s = "";
        for(; mit != marcados->end(); mit++) s += std::to_string((*mit)) + ",";
        s += std::to_string(0) + ",";
        s += std::to_string(soma);
        ca_CaminhoMin.push_back(s);

      } else if(soma == ca_SomaMin) {
        std::string s = "";
        for(; mit != marcados->end(); mit++) s += std::to_string((*mit)) + ",";
        s += std::to_string(0) + ",";
        s += std::to_string(soma);
        ca_CaminhoMin.push_back(s);
      }

      soma -= a->getWeight();
      printado = 1;
    }

    if(visited[(*it)->id] == false) {
      construirArvore((*it), visited, marcados);
      visited[(*it)->id] = false;
      Aresta* a = v->procuraAresta(marcados->back());
      soma -= a->getWeight();
      marcados->pop_back();
      caminhou = 1;
    }
  }
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
  if(distancia <= 0)  // nao aceitamos distancia negativa ou nula
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
  if(v1 == nullptr || v2 == nullptr)  // verifica se algum dos dois nao encontra-se na lista
    return nullptr;

  return v1->adicionarAresta(v2, distancia);
}

Aresta* Grafo::adicionarAresta(int id1, int id2, int distancia) {
  if(distancia <= 0)  // nao aceitamos distancia negativa ou nula
    return nullptr;

  std::list<Vertice*>::const_iterator it = this->vertices->cbegin();
  Vertice* v1 = nullptr;
  Vertice* v2 = nullptr;
  int achado = 0;

  for(; it != this->vertices->end(); it++) {
    if((*it)->getId() == id1) {
      v1 = (*it);
      achado++;
    } else if((*it)->getId() == id2) {
      v2 = (*it);
      achado++;
    }
    if(achado == 2) break;
  }
  if(v1 == nullptr || v2 == nullptr)  // verifica se algum dos dois nao encontra-se na lista
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
    // std::cout << "Vertice V" << (*it)->getId() << "(" << (*it)->getX() << ")(" << (*it)->getY()
    // << ")" << "\t Ligacoes: "; //imprime com a pos x e y
    std::cout << "Vertice " << (*it)->getName() << "\t Ligacoes: ";  // imprime sem a pos x e y
    (*it)->imprimirLigacoes();
  }
}

const std::list<Vertice*>* Grafo::getVertices() const { return vertices; }