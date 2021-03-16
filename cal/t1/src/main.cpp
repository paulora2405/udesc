#include <algorithm>
#include <iostream>

#include "biblioteca.hpp"

using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  if(argc != 1) {
    cout << "Quantidade de argumentos errada\n";
    exit(1);
  }

  extended_euclidean();
}
