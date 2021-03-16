#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <gmp.h>

#include <algorithm>
#include <iostream>

void extended_euclidean() {
  mpz_t a, b, c;
  mpz_inits(a, b, c, NULL);

  mpz_set_str(a, "1234", 10);
  mpz_set_str(b, "-5678", 10);

  mpz_add(c, a, b);
  std::cout << "Result = ";
  mpz_out_str(stdout, 10, c);
  std::cout << '\n';
}

#endif
