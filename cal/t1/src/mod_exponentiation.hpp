#ifndef MOD_EXPONENTIATION_HPP
#define MOD_EXPONENTIATION_HPP

/*
 * Para ser realmente segura, a potenciação modular não deve deixar rastros da chave.
 * https://crypto.stackexchange.com/questions/75408/efficient-function-algorithm-method-to-do-modular-exponentiation
 */

long long mod_pow_fast(long long base, long long power, long long n) {
  long long result = 1;

  while(power > 0) {
    if(power % 2 == 1) result = (result * base) % n;

    power /= 2;

    base = (base * base) % n;
  }

  return result;
}

long long mod_pow_const_time(long long base, long long power, long long n) {
  long long result = 1;
  long long result_temp = 1;

  while(power > 0) {
    if(power % 2 == 1) result = (result * base) % n;
    // else
    //   result_temp = (result * base) % n;

    power /= 2;

    base = (base * base) % n;
  }

  return result;
}

long long mod_pow_const_time_and_cond_copy(long long base, long long power, long long n) {
  long long result = 1;

  while(power > 0) {
    bool sBit = power % 2 == 1;

    result = ((result * base) % n) * sBit + (1 - sBit) * result;

    power /= 2;

    base = (base * base) % n;
  }

  return result;
}

#endif