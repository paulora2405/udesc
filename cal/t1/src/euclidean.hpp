#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

int gcd(long long a, long long b) {
  if(b > a) (a ^= b), (b ^= a), (a ^= b);

  long long r = a % b;
  if(r == 0)
    return b;
  else
    return gcd(b, r);
}

int gcd_iter(int num1, int num2) {
  int r;

  do {
    r = num1 % num2;

    num1 = num2;
    num2 = r;

  } while(r != 0);

  return num1;
}

long long euclides_extended(long long m, long long n, long long &a, long long &b) {
  if(n == 0) {
    a = 1;
    b = 0;
    return m;
  } else {
    long long e, f, d;

    d = euclides_extended(n, m % n, e, f);

    a = f;
    b = e - f * (m / n);

    return d;
  }
}

#endif