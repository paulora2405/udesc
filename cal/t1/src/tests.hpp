#ifndef TESTS_HPP
#define TESTS_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "file_manipulation.hpp"
#include "mod_exponentiation.hpp"

void encrypt_test() {
  using namespace boost::multiprecision;

  std::string msg = "123456789\n987654321\n123456789\n987654321\n";
  std::string srcname = "tests.bin";
  write_file(srcname, msg);

  // READ FROM OG FILE
  std::ifstream src(srcname, std::ios::binary);

  uint128_t buffer;
  std::vector<uint128_t> input;

  /*
  40 / 32 = 1
  len_file / sizeof(uint128_t)
  40 % 32 = 6
  len_file % sizeof(uint128_t)
  */
  src.seekg(0, src.end);
  size_t len_file = src.tellg();
  size_t int_len = len_file / sizeof(uint128_t);
  size_t rem_len = len_file % sizeof(uint128_t);
  src.seekg(0, src.beg);

  std::cout << len_file << std::endl;
  std::cout << int_len << std::endl;
  std::cout << rem_len << std::endl;

  src.read(reinterpret_cast<char *>(&buffer), sizeof(uint128_t));
  input.push_back(buffer);

  if(rem_len != 0) {
    src.read(reinterpret_cast<char *>(&buffer), rem_len);
    input.push_back(buffer);
  }
  src.close();

  // DATA MANIPULATION HERE
  std::vector<uint128_t> output(input.size(), 0);

  for(size_t i = 0; i < input.size(); i++) {
    uint128_t a = 2;
    output[i] = input[i] * a;
  }

  // WRITE TO ENCYPTED FILE
  std::string dstname = "tests2.bin";
  std::ofstream dst(dstname, std::ios::binary);

  for(size_t i = 0; i < int_len; i++) {
    buffer = output[i];
    dst.write(reinterpret_cast<const char *>(&buffer), sizeof(uint128_t));
  }
  if(rem_len != 0) {
    buffer = output.back();
    dst.write(reinterpret_cast<const char *>(&buffer), rem_len);
  }

  dst.close();
}

#endif