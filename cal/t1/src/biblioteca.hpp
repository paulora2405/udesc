#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <gmp.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

typedef long long ll;

void exemplo_gmp() {
  mpz_t a, b, c;
  mpz_inits(a, b, c, NULL);

  mpz_set_str(a, "1234", 10);
  mpz_set_str(b, "-5678", 10);

  mpz_add(c, a, b);
  std::cout << "Result = ";
  mpz_out_str(stdout, 10, c);
  std::cout << '\n';

  mpz_clears(a, b, c);
}

void initialize_ll() {
  ll p, q, n, phin, e, d, aux;
  // Passo 1
  p = 7;
  q = 2;

  // Passo 2
  n = p * q;

  // Passo 3
  phin = (p - 1) * (q - 1);

  // Passo 4
  do {
    e = 5;
  } while(e <= phin || gcd(e, phin) != 1);

  // Passo 5
}

void initialize_mpz() {
  mpz_t p, q, n, phin, e, d, aux;
  mpz_inits(p, q, n, phin, e, d, aux);

  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  mpz_set_ui(p, 2);
  mpz_set_ui(q, 7);

  // Passo 2: Calcular n = p * q
  mpz_mul(n, p, n);

  // Passo 3: Calular ø(n) = (p - 1)*(q - 1)
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

int gcd(ll a, ll b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  ll r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

void replace_by_two(ll &x, ll &y, ll quotient) {
  ll aux = x;
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

void extended_euclidean(ll a, ll b) {
  ll r, old_r, s, old_s, t, old_t, aux, quotient;

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

// ll power(ll base, ll e, ll mod) {
//   ll result = 1;
//   base %= mod;
//   while(e) {
//     if(e & 1) result = (__int128)result * base % mod;
//     base = (__int128)base * base % mod;
//     e >>= 1;
//   }
//   return result;
// }

// bool is_composite(ll n, ll a, ll d, int s) {
//   ll x = power(a, d, n);
//   if(x == 1 || x == n - 1) return false;
//   for(int r = 1; r < s; r++) {
//     x = (__int128)x * x % n;
//     if(x == n - 1) return false;
//   }
//   return true;
// }

// bool miller_rabin(ll n) {
//   if(n < 2) return false;
//   int r = 0;
//   ll d = n - 1;
//   while((d & 1) == 0) d >>= 1, ++r;
//   for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
//     if(n == a) return true;
//     if(is_composite(n, a, d, r)) return false;
//   }
//   return true;
// }

#endif
