#ifndef KEY_GENERATOR_HPP
#define KEY_GENERATOR_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>

#include "big_int_type.hpp"
#include "euclidean.hpp"
#include "primality.hpp"

typedef struct key {
  big_int d_e;
  big_int n;
} Key;

typedef struct key_pair {
  Key pub_key;
  Key priv_key;
} Key_pair;

/*
 * Gera os valores de p, q, n, Phi(n), e, d.
 * @returns Um par de chaves, contendo uma chave pública e uma chave privada.
 */
Key_pair initialize_128(unsigned max_bits, bool print = false);

#endif