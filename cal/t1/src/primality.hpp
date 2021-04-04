#ifndef PRIMALITY_HPP
#define PRIMALITY_HPP

#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <cmath>
#include <iostream>

#include "big_int_type.hpp"
#include "mod_exponentiation.hpp"
#include "random_generator_seed.hpp"

bool is_composite(big_int n, int a, big_int d, big_int s) {
  big_int x = mod_pow_const_time_and_cond_copy(a, d, n);
  if(x == 1 || x == n - 1) return false;
  for(big_int r = 1; r < s; r++) {
    x = (big_int)x * x % n;
    if(x == n - 1) return false;
  }
  return true;
}

bool miller_rabin(big_int n) {
  if(n < 2) return false;
  big_int r = 0;
  big_int d = n - 1;
  while((d & 1) == 0) d >>= 1, ++r;
  for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if(n == a) return true;
    if(is_composite(n, a, d, r)) return false;
  }
  return true;
}

/*
 * Gera um número primo aleatório no intervalo [lowerbound, upperbound].
 */
big_int random_prime(big_int upperbound) {
  using namespace boost::multiprecision;
  int casas = 0;
  while(upperbound > 1) {
    casas++;
    upperbound = upperbound / 10;
  }

  boost::random::uniform_int_distribution<int64_t> rand_64(2, (int64_t)pow(10, casas / 2) - 1);

  big_int int_left = rand_64(gen_128);
  big_int int_right = rand_64(gen_128);
  big_int candidate;
  candidate = int_left * (int64_t)pow(10, casas / 2) + int_right;

  candidate += !(candidate & 1);

  while(!miller_rabin(candidate)) {
    candidate += 2;
    if(candidate > upperbound) {
      int_left = rand_64(gen_128);
      int_right = rand_64(gen_128);
      candidate = int_left * (int64_t)pow(10, casas / 2) + int_right;
      candidate += !(candidate & 1);
    }
  }
  return candidate;
}

#endif
