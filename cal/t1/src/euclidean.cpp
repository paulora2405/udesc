#include "../include/euclidean.hpp"

big_int gcd(big_int a, big_int b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  big_int r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

big_int gcd_iter(big_int num1, big_int num2) {
  while(num2) {
    num1 %= num2;
    std::swap(num1, num2);
  }
  return num1;
}

big_int euclides_extended(big_int a, big_int b, big_int &x, big_int &y) {
  x = 1, y = 0;
  big_int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while(b1) {
    big_int q = a1 / b1;
    std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
    std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
    std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
  }
  return a1;
}