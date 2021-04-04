#ifndef TESTS_HPP
#define TESTS_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "file_manipulation.hpp"
#include "key_generator.hpp"
#include "mod_exponentiation.hpp"

void int_limits() {
  using namespace boost::multiprecision;
  using std::cout;
  using std::endl;
  cout << ((cpp_int(1) << 16) - 1) << endl;
  cout << ((cpp_int(1) << 32) - 1) << endl;
  cout << ((cpp_int(1) << 64) - 1) << endl;
  cout << ((cpp_int(1) << 128) - 1) << endl;

  int x = 255;
  int n = 0;
  do {
    x >>= 8;
    n++;
  } while(x != 0);
  // cout << n << endl;
}

#endif