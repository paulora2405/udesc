#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <gmp.h>

#include <cstdint>
#include <iostream>
#include <random>

#include "euclidean.hpp"
#include "gerador_aleatorio.hpp"
#include "primalidade.hpp"

long long get_e_value(long long phin) {
  std::uniform_int_distribution<int> rand_int(2, phin - 1);
  long long e;
  do {
    e = abs(rand_int(generator));
  } while(gcd(e, phin) != 1);
  return e;
}

void print_keys(long long &p, long long &q, long long &n, long long &phin, long long &e,
                long long &d) {
  std::cout << "The values calculated were:" << std::endl;
  std::cout << "P = " << p << std::endl;
  std::cout << "Q = " << q << std::endl;
  std::cout << "N = " << n << std::endl;
  std::cout << "Phi(N) = " << phin << std::endl;
  std::cout << "E = " << e << std::endl;
  std::cout << "D = " << d << std::endl;
}

void initialize_ll() {
  long long p, q, n, phin, e, d;
  long long upper_bound = 50;
  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  p = random_prime(upper_bound);
  do {
    q = random_prime(upper_bound);
  } while(q == p);

  // Passo 2: Calcular n = p * q
  n = p * q;

  // Passo 3
  phin = (p - 1) * (q - 1);

  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  do {
    // implementar valor de e
    e = get_e_value(phin);
  } while(e > phin || gcd(e, phin) != 1);

  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
  // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
  long long tmp;
  euclides_extended(e, phin, &d, &tmp);
  if(d < 0) d += phin;

  // Imprimir os resultados
  print_keys(p, q, n, phin, e, d);
}

void initialize_mpz() {
  mpz_t p, q, n, phin, e, d, aux;
  mpz_inits(p, q, n, phin, e, d, aux);

  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  mpz_set_ui(p, 2);
  mpz_set_ui(q, 7);

  // Passo 2: Calcular n = p * q
  mpz_mul(n, p, n);

  // Passo 3: Calcular ø(n) = (p - 1)*(q - 1)
  mpz_sub_ui(aux, p, 1);
  mpz_set(phin, aux);
  mpz_sub_ui(aux, q, 1);
  mpz_mul(phin, aux, phin);

  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  do {
    mpz_set_ui(e, 5);
    mpz_gcd(aux, e, phin);
  } while(mpz_cmp(e, phin) <= 0 || mpz_cmp_ui(aux, 1) != 0);

  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
  // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
  mpz_invert(d, e, phin);

  mpz_clears(p, q, n, phin, e, d, aux);
}

#endif
