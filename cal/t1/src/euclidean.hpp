#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <boost/multiprecision/cpp_int.hpp>

#include "big_int_type.hpp"

long long gcd(long long a, long long b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  long long r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

big_int gcd_iter(big_int num1, big_int num2) {
  if(num2 > num1) (num1 ^= num2), (num2 ^= num1), (num1 ^= num2);

  big_int r;
  do {
    r = num1 % num2;

    num1 = num2;
    num2 = r;

  } while(r != 0);

  return num1;
}

big_int euclides_extended(big_int m, big_int n, big_int &a, big_int &b) {
  if(n == 0) {
    a = 1;
    b = 0;
    return m;
  } else {
    big_int e, f, d;

    d = euclides_extended(n, m % n, e, f);

    a = f;
    b = e - f * (m / n);

    return d;
  }
}

#endif