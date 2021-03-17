#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <gmp.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

typedef long long ll;

std::random_device myRandomDevice;
unsigned int seed = myRandomDevice();
std::default_random_engine generator(seed);

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

int gcd(ll a, ll b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  ll r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

int mdc(int num1, int num2) {
  int resto;

  do {
    resto = num1 % num2;

    num1 = num2;
    num2 = resto;

  } while(resto != 0);

  return num1;
}

ll get_e_value(ll phin) {
  std::uniform_int_distribution<int> rand_int(2, phin - 1);
  ll e;
  do {
    e = abs(rand_int(generator));
  } while(gcd(e, phin) != 1);
  return e;
}

bool is_prime_naive(ll n) {
  if(n == 0 || n == 1) return false;

  for(ll i = 2; i < n; i++)
    if(n % i == 0) return false;

  return true;
}

bool miller_rabin(ll n);

ll random_prime(ll upperbound) {
  std::uniform_int_distribution<int> rand_int(2, upperbound);
  ll candidate;
  do {
    candidate = rand_int(generator);
  } while(!miller_rabin(candidate));
  // } while(!is_prime_naive(candidate));
  return candidate;
}

ll gcd_extended(ll a, ll b, ll *x, ll *y);
ll euclides_r_x(ll m, ll n, ll *a, ll *b);

void initialize_ll() {
  ll p, q, n, phin, e, d, aux;
  ll upper_bound = 100;
  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  // p = random_prime(upper_bound);
  // do {
  //   q = random_prime(upper_bound);
  // } while(q == p);

  p = 11;
  q = 13;

  std::cout << "P=" << p << std::endl;
  std::cout << "Q=" << q << std::endl;

  // Passo 2: Calcular n = p * q
  n = p * q;
  std::cout << "N=" << n << std::endl;

  // Passo 3
  phin = (p - 1) * (q - 1);
  std::cout << "Phi(n)=" << phin << std::endl;

  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  do {
    // implementar valor de e
    e = get_e_value(phin);
  } while(e > phin || gcd(e, phin) != 1);
  std::cout << "E=" << e << std::endl;
  std::cout << "GCD(E, Phi)=" << gcd(e, phin) << std::endl;

  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))
  // IMPLEMENTAR ALGORITMO EUCLIDIANO EXTENDIDO AQUI
  ll tmp;
  euclides_r_x(e, phin, &d, &tmp);
  if(d < 0) d += phin;
  std::cout << "D=" << d << std::endl;
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

void replace_by_two(ll &x, ll &y, ll quotient) {
  ll aux = x;
  x = y - quotient * x;
  y = aux;
}

ll gcd_extended(ll a, ll b, ll *x, ll *y) {
  if(a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  ll x1, y1;
  ll gcd = gcd_extended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}

ll euclides_r_x(ll m, ll n, ll *a, ll *b) {
  ll d;

  if(n == 0) {
    *a = 1;
    *b = 0;
    return m;
  } else {
    ll e, f;

    d = euclides_r_x(n, m % n, &e, &f);

    /* Neste ponto vale que
          d == e*n + f*(m%n)
            == e*n + f*(m - (m/n)*n)
            == f*m + (e - f*(m/n))*n   */

    *a = f;
    *b = e - f * (m / n);

    return d;
  }
}

ll power(ll base, ll e, ll mod) {
  ll result = 1;
  base %= mod;
  while(e) {
    if(e & 1) result = (ll)result * base % mod;
    base = (ll)base * base % mod;
    e >>= 1;
  }
  return result;
}

bool is_composite(ll n, ll a, ll d, int s) {
  ll x = power(a, d, n);
  if(x == 1 || x == n - 1) return false;
  for(int r = 1; r < s; r++) {
    x = (ll)x * x % n;
    if(x == n - 1) return false;
  }
  return true;
}

bool miller_rabin(ll n) {
  if(n < 2) return false;
  int r = 0;
  ll d = n - 1;
  while((d & 1) == 0) d >>= 1, ++r;
  for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if(n == a) return true;
    if(is_composite(n, a, d, r)) return false;
  }
  return true;
}

#endif
