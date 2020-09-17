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
  g->algoritmos();
  delete g;
}