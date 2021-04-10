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

// template <class T>
// Prime_generator<T>::Prime_generator(unsigned seed) {
//   mt19937_gen128.seed(seed);
// }

// template <class T>
// bool Prime_generator<T>::is_composite(T n, int a, T d, T s) {
//   T x = mod_pow(a, d, n);
//   if(x == 1 || x == n - 1) return false;
//   for(T r = 1; r < s; r++) {
//     x = (T)x * x % n;
//     if(x == n - 1) return false;
//   }
//   return true;
// }

// template <class T>
// bool Prime_generator<T>::miller_rabin(T n) {
//   if(n < 2) return false;
//   T r = 0;
//   T d = n - 1;
//   while((d & 1) == 0) d >>= 1, ++r;
//   for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
//     if(n == a) return true;
//     if(is_composite(n, a, d, r)) return false;
//   }
//   return true;
// }

// template <class T>
// T Prime_generator<T>::random_prime(unsigned max_bits) {
//   T max_num = (T{1}) << max_bits;
//   // using namespace boost::multiprecision;
//   // int casas = 0;
//   // while(upperbound > 1) {
//   //   casas++;
//   //   upperbound = upperbound / 10;
//   // }

//   // boost::random::uniform_int_distribution<int64_t> rand_64(2, (int64_t)pow(10, casas / 2) -
//   1); boost::random::uniform_int_distribution<boost::multiprecision::cpp_int> dist(2, max_num);

//   // T int_left = rand_64(mt19937_gen128);
//   // T int_right = rand_64(mt19937_gen128);
//   this->prime = dist(mt19937_gen128);
//   // this->prime = int_left * (int64_t)pow(10, casas / 2) + int_right;

//   this->prime += !(this->prime & 1);

//   while(!miller_rabin(this->prime)) {
//     this->prime += 2;
//     if(this->prime > max_num) {
//       // int_left = rand_64(mt19937_gen128);
//       // int_right = rand_64(mt19937_gen128);
//       // this->prime = int_left * (int64_t)pow(10, casas / 2) + int_right;
//       this->prime = dist(mt19937_gen128);
//       this->prime += !(this->prime & 1);
//     }
//   }
//   return this->prime;
// }