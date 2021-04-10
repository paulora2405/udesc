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