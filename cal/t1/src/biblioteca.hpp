#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <gmp.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

void exemplo_gmp() {
  mpz_t a, b, c;
  mpz_inits(a, b, c, NULL);

  mpz_set_str(a, "1234", 10);
  mpz_set_str(b, "-5678", 10);

  mpz_add(c, a, b);
  std::cout << "Result = ";
  mpz_out_str(stdout, 10, c);
  std::cout << '\n';
}

int gcd(long long a, long long b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  long long r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

void replace_by_two(long long &x, long long &y, long long quotient) {
  long long aux = x;
  x = y - quotient * x;
  y = aux;
}

int gcdExtended(int a, int b, int *x, int *y) {
  if(a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  int x1, y1;
  int gcd = gcdExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}

void extended_euclidean(long long a, long long b) {
  long long r, old_r, s, old_s, t, old_t, aux, quotient;

  old_r = a;
  r = b;
  old_s = 1;
  s = 0;
  old_t = 0;
  t = 1;

  while(r != 0) {
    quotient = old_r / r;
    replace_by_two(old_r, r, quotient);
    replace_by_two(old_s, s, quotient);
    replace_by_two(old_t, t, quotient);
  }

  std::cout << "Coeficiente: " << old_s << " " << old_t << std::endl;
  std::cout << "GCD: " << old_r << std::endl;
  std::cout << "Quocientes do gcd: " << t << " " << s << std::endl;
}

// long long power(long long base, long long e, long long mod) {
//   long long result = 1;
//   base %= mod;
//   while(e) {
//     if(e & 1) result = (__int128)result * base % mod;
//     base = (__int128)base * base % mod;
//     e >>= 1;
//   }
//   return result;
// }

// bool is_composite(long long n, long long a, long long d, int s) {
//   long long x = power(a, d, n);
//   if(x == 1 || x == n - 1) return false;
//   for(int r = 1; r < s; r++) {
//     x = (__int128)x * x % n;
//     if(x == n - 1) return false;
//   }
//   return true;
// }

// bool miller_rabin(long long n) {
//   if(n < 2) return false;
//   int r = 0;
//   long long d = n - 1;
//   while((d & 1) == 0) d >>= 1, ++r;
//   for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
//     if(n == a) return true;
//     if(is_composite(n, a, d, r)) return false;
//   }
//   return true;
// }

#endif
