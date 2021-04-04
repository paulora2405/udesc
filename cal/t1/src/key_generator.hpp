#ifndef KEY_GENERATOR_HPP
#define KEY_GENERATOR_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <random>

#include "big_int_type.hpp"
#include "euclidean.hpp"
#include "primality.hpp"
#include "random_generator_seed.hpp"

struct Key {
  big_int d_e;
  big_int n;
};

struct Key_pair {
  struct Key pub_key;
  struct Key priv_key;
};

big_int get_e_value(big_int phin) {
  using namespace boost::multiprecision;

  int casas = 0;
  big_int phin_cp = phin;
  while(phin_cp >= 10) {
    casas++;
    phin_cp = phin_cp / 10;
  }

  boost::random::uniform_int_distribution<int64_t> rand_64(2, (int64_t)pow(10, casas / 2) - 1);

  big_int int_left = rand_64(gen_128);
  big_int int_right = rand_64(gen_128);
  big_int e = int_left * (int64_t)pow(10, casas / 2) + int_right;

  e += !(e & 1);
  while(gcd_iter(e, phin) != 1) {
    e += 2;
    if(e >= phin) {
      int_left = rand_64(gen_128);
      int_right = rand_64(gen_128);
      e = int_left * (int64_t)pow(10, casas / 2) + int_right;
      e += !(e & 1);
    }
  }

  return e;
}

/*
 * Gera os valores de p, q, n, Phi(n), e, d.
 * @returns Um par de chaves, contendo uma chave pública e uma chave privada.
 */
struct Key_pair initialize_128(big_int upperbound, bool print) {
  big_int p, q, n, phin, e, d;
  big_int upperbound_pq(sqrt(upperbound));
  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  p = random_prime(upperbound_pq);
  do {
    q = random_prime(upperbound_pq);
  } while(q == p);

  // Passo 2: Calcular n = p * q
  n = p * q;

  // Passo 3
  phin = (p - 1) * (q - 1);

  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  e = get_e_value(phin);

  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
  // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
  big_int tmp;
  euclides_extended(e, phin, d, tmp);
  if(d < 0) d += phin;

  // Imprimir os resultados
  if(print) {
    std::cout << "Upperbound for N: " << upperbound << std::endl;
    std::cout << "The values calculated were:" << std::endl;
    std::cout << "P = " << p << std::endl;
    std::cout << "Q = " << q << std::endl;
    std::cout << "N = " << n << std::endl;
    std::cout << "Phi(N) = " << phin << std::endl;
    std::cout << "E = " << e << std::endl;
    std::cout << "D = " << d << std::endl;
  }

  struct Key pub = {n, e};
  struct Key priv = {n, d};
  struct Key_pair pair = {pub, priv};

  return pair;
}

#endif
