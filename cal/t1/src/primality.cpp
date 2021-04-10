#include "../include/primality.hpp"

Prime_generator::Prime_generator(unsigned seed) {
  mt19937_gen128.seed(seed);
}

bool Prime_generator::is_composite(big_int n, int a, big_int d, big_int s) {
  big_int x = mod_pow(a, d, n);
  if(x == 1 || x == n - 1) return false;
  for(big_int r = 1; r < s; r++) {
    x = (big_int)x * x % n;
    if(x == n - 1) return false;
  }
  return true;
}

bool Prime_generator::miller_rabin(big_int n) {
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

big_int Prime_generator::random_prime(unsigned max_bits) {
  big_int max_num = (big_int{1}) << max_bits;

  boost::random::uniform_int_distribution<boost::multiprecision::cpp_int> dist(2, max_num);

  this->prime = (big_int)dist(mt19937_gen128);

  this->prime += !(this->prime & 1);

  while(!miller_rabin(this->prime)) {
    this->prime += 2;
    if(this->prime > max_num) {
      this->prime = (big_int)dist(mt19937_gen128);
      this->prime += !(this->prime & 1);
    }
  }
  return this->prime;
}