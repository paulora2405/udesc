#ifndef MOD_EXPONENTIATION_HPP
#define MOD_EXPONENTIATION_HPP

#include <boost/multiprecision/cpp_int.hpp>

#include "big_int_type.hpp"

/*
 * Para ser realmente segura, a potenciação modular não deve deixar rastros da chave.
 * https://crypto.stackexchange.com/questions/75408/efficient-function-algorithm-method-to-do-modular-exponentiation
 */

// Mod pow in constant time with conditional copy
big_int mod_pow(big_int base_, big_int power_, big_int n_);

// long long mod_pow_fast(long long base, long long power, long long n);

// long long mod_pow_const_time(long long base, long long power, long long n);

#endif