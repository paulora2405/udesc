#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <boost/multiprecision/cpp_int.hpp>

long long gcd(long long a, long long b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  long long r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

boost::multiprecision::int128_t gcd_iter(boost::multiprecision::int128_t num1,
                                         boost::multiprecision::int128_t num2) {
  if(num2 > num1) (num1 ^= num2), (num2 ^= num1), (num1 ^= num2);

  boost::multiprecision::int128_t r;
  do {
    r = num1 % num2;

    num1 = num2;
    num2 = r;

  } while(r != 0);

  return num1;
}

boost::multiprecision::int128_t euclides_extended(boost::multiprecision::int128_t m,
                                                  boost::multiprecision::int128_t n,
                                                  boost::multiprecision::int128_t &a,
                                                  boost::multiprecision::int128_t &b) {
  if(n == 0) {
    a = 1;
    b = 0;
    return m;
  } else {
    boost::multiprecision::int128_t e, f, d;

    d = euclides_extended(n, m % n, e, f);

    a = f;
    b = e - f * (m / n);

    return d;
  }
}

#endif