#ifndef KEY_GENERATOR_HPP
#define KEY_GENERATOR_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <random>

#include "euclidean.hpp"
#include "primality.hpp"
#include "random_generator_seed.hpp"

struct Public_key {
  boost::multiprecision::int128_t n;
  boost::multiprecision::int128_t e;
};

struct Private_key {
  boost::multiprecision::int128_t n;
  boost::multiprecision::int128_t d;
};

struct Key_pair {
  struct Public_key pub_key;
  struct Private_key priv_key;
};

boost::multiprecision::int128_t get_e_value(boost::multiprecision::int128_t phin) {
  // boost::random::uniform_int_distribution<boost::multiprecision::int128_t> rand_128(2, phin - 1);
  boost::multiprecision::int128_t e;
  do {
    // e = abs(rand_128(gen_128));
  } while(gcd_iter(e, phin) != 1);
  return e;
}

void print_keys(boost::multiprecision::int128_t &p, boost::multiprecision::int128_t &q,
                boost::multiprecision::int128_t &n, boost::multiprecision::int128_t &phin,
                boost::multiprecision::int128_t &e, boost::multiprecision::int128_t &d) {
  std::cout << "The values calculated were:" << std::endl;
  std::cout << "P = " << p << std::endl;
  std::cout << "Q = " << q << std::endl;
  std::cout << "N = " << n << std::endl;
  std::cout << "Phi(N) = " << phin << std::endl;
  std::cout << "E = " << e << std::endl;
  std::cout << "D = " << d << std::endl;
}

/*
 * Gera os valores de p, q, n, Phi(n), e, d.
 * @returns Um par de chaves, contendo uma chave pública e uma chave privada.
 */
// struct Key_pair initialize_ll(long long lowerbound, long long upperbound) {
//   long long p, q, n, phin, e, d;

//   // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
//   p = random_prime(lowerbound, upperbound);
//   do {
//     q = random_prime(lowerbound, upperbound);
//   } while(q == p);

//   // Passo 2: Calcular n = p * q
//   n = p * q;

//   // Passo 3
//   phin = (p - 1) * (q - 1);

//   // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
//   e = get_e_value(phin);

//   // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
//   // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
//   long long tmp;
//   euclides_extended(e, phin, d, tmp);
//   if(d < 0) d += phin;

//   // Imprimir os resultados
//   print_keys(p, q, n, phin, e, d);

//   struct Public_key pub = {n, e};
//   struct Private_key priv = {n, d};
//   struct Key_pair pair = {pub, priv};

//   return pair;
// }

/*
 * Gera os valores de p, q, n, Phi(n), e, d.
 * @returns Um par de chaves, contendo uma chave pública e uma chave privada.
 */
struct Key_pair initialize_128(boost::multiprecision::int128_t upperbound) {
  boost::multiprecision::int128_t p, q, n, phin, e, d;
  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  p = random_prime(upperbound);
  do {
    q = random_prime(upperbound);
  } while(q == p);

  // Passo 2: Calcular n = p * q
  n = p * q;

  // Passo 3
  phin = (p - 1) * (q - 1);

  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  e = get_e_value(phin);

  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
  // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
  boost::multiprecision::int128_t tmp;
  euclides_extended(e, phin, d, tmp);
  if(d < 0) d += phin;

  // Imprimir os resultados
  print_keys(p, q, n, phin, e, d);

  struct Public_key pub = {n, e};
  struct Private_key priv = {n, d};
  struct Key_pair pair = {pub, priv};

  return pair;
}

#endif
