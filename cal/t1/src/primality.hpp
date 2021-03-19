#ifndef PRIMALIDADE_HPP
#define PRIMALIDADE_HPP

#include <algorithm>

#include "mod_exponentiation.hpp"
#include "random_generator_seed.hpp"

bool is_composite(long long n, long long a, long long d, int s) {
  long long x = mod_pow_const_time_and_cond_copy(a, d, n);
  if(x == 1 || x == n - 1) return false;
  for(int r = 1; r < s; r++) {
    x = (long long)x * x % n;
    if(x == n - 1) return false;
  }
  return true;
}

bool miller_rabin(long long n) {
  if(n < 2) return false;
  int r = 0;
  long long d = n - 1;
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
long long random_prime(long long lowerbound, long long upperbound) {
  std::uniform_int_distribution<int> rand_int(lowerbound, upperbound);
  long long candidate;
  candidate = rand_int(generator);

  if(!(candidate & 1)) candidate++;

  while(!miller_rabin(candidate)) {
    candidate += 2;
  }
  return candidate;
}

#endif