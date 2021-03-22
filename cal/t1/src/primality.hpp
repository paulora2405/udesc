#ifndef PRIMALITY_HPP
#define PRIMALITY_HPP

#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <cmath>
#include <iostream>

#include "mod_exponentiation.hpp"
#include "random_generator_seed.hpp"

bool is_composite(boost::multiprecision::int128_t n, int a, boost::multiprecision::int128_t d,
                  boost::multiprecision::int128_t s) {
  boost::multiprecision::int128_t x = mod_pow_const_time_and_cond_copy(a, d, n);
  if(x == 1 || x == n - 1) return false;
  for(boost::multiprecision::int128_t r = 1; r < s; r++) {
    x = (boost::multiprecision::int128_t)x * x % n;
    if(x == n - 1) return false;
  }
  return true;
}

bool miller_rabin(boost::multiprecision::int128_t n) {
  if(n < 2) return false;
  boost::multiprecision::int128_t r = 0;
  boost::multiprecision::int128_t d = n - 1;
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
boost::multiprecision::int128_t random_prime(boost::multiprecision::int128_t upperbound) {
  int casas = 0;
  while(upperbound > 1) {
    casas++;
    upperbound = upperbound / 10;
  }

  boost::random::uniform_int_distribution<long long> rand_ll(2, (long long)pow(10, casas / 2) - 1);

  long long int_left = rand_ll(gen_128);
  long long int_right = rand_ll(gen_128);
  boost::multiprecision::int128_t candidate;
  candidate = int_left * (long long)pow(10, casas / 2) + int_right;

  if(!(candidate & 1)) candidate++;

  while(!miller_rabin(candidate)) {
    candidate += 2;
    if(candidate > upperbound) {
      int_left = rand_ll(gen_128);
      int_right = rand_ll(gen_128);
      candidate = int_left * (long long)pow(10, casas / 2) + int_right;
    }
    candidate += !(candidate & 1);
  }
  return candidate;
}

#endif
