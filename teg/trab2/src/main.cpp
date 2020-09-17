/**
    BCC-20 TEG : Main
    @file main.cpp
    @author Paulo Albuquerque & Menderson
    @version 1.0 09/08/20
*/
#include <iostream>

#include "Aresta.hpp"
#include "Grafo.hpp"
#include "Vertice.hpp"

int main() {
  Grafo* g{new Grafo()};

  // FILE* f = fopen("melhorCaminho.txt", "w");
  // fclose(f);

  // std::cout << "Imprimindo grafo completo" << std::endl;
  // g->imprimirGrafo();
  g->construirArvore("Joinville");
  // f = fopen("melhorCaminho.txt", "a");

  delete g;
  return 0;
}