#ifndef PRIMALITY_HPP
#define PRIMALITY_HPP

#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/random.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

#include "big_int_type.hpp"
#include "mod_exponentiation.hpp"

class Prime_generator {
private:
  big_int prime;
  boost::random::mt19937 mt19937_gen128;

public:
  Prime_generator() {}
  Prime_generator(unsigned seed);

  bool is_composite(big_int n, int a, big_int d, big_int s);

  bool miller_rabin(big_int n);

  /*
   * Gera um número primo aleatório no intervalo.
   */
  big_int random_prime(unsigned max_bits);
};

#endif