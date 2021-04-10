#include "../include/mod_exponentiation.hpp"

big_int mod_pow(big_int base_, big_int power_, big_int n_) {
  boost::multiprecision::cpp_int result{1};
  boost::multiprecision::cpp_int base{base_};
  boost::multiprecision::cpp_int power{power_};

  while(power > 0) {
    bool sBit = power % 2 == 1;

    result = ((result * base) % n_) * sBit + (1 - sBit) * result;

    power /= 2;

    base = (base * base) % n_;
  }

  big_int ret{result};
  return ret;
}

// template <class T>
// T mod_pow(T &base_, T &power_, T &n_) {
//   boost::multiprecision::cpp_int result{1};
//   boost::multiprecision::cpp_int base{base_};
//   boost::multiprecision::cpp_int power{power_};

//   while(power > 0) {
//     bool sBit = power % 2 == 1;

//     result = ((result * base) % n_) * sBit + (1 - sBit) * result;

//     power /= 2;

//     base = (base * base) % n_;
//   }

//   T ret{result};
//   return ret;
// }

// long long mod_pow_fast(long long base, long long power, long long n) {
//   long long result = 1;

//   while(power > 0) {
//     if(power % 2 == 1) result = (result * base) % n;

//     power /= 2;

//     base = (base * base) % n;
//   }

//   return result;
// }

// long long mod_pow_const_time(long long base, long long power, long long n) {
//   long long result = 1;
//   // long long result_temp = 1;

//   while(power > 0) {
//     if(power % 2 == 1) result = (result * base) % n;
//     // else
//     //   result_temp = (result * base) % n;

//     power /= 2;

//     base = (base * base) % n;
//   }

//   return result;
// }
