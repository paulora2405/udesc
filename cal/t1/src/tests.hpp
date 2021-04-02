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

  std::string msg = "abcdefghijklmnopqrstuvwxyz123456";
  std::string srcname = "tests.bin";
  write_file(srcname, msg);

  // READ FROM OG FILE
  std::ifstream src(srcname, std::ios::binary);

  int128_t buffer;
  std::vector<int128_t> input;

  /*
  40 / 32 = 1
  len_file / sizeof(uint128_t)
  40 % 32 = 6
  len_file % sizeof(uint128_t)
  */
  src.seekg(0, src.end);
  size_t custom_size = sizeof(int128_t) / 4;
  size_t len_file = src.tellg();
  size_t int_len = len_file / custom_size;
  size_t rem_len = len_file % custom_size;
  src.seekg(0, src.beg);

  std::cout << len_file << std::endl;
  std::cout << int_len << std::endl;
  std::cout << rem_len << std::endl;

  for(size_t i = 0; i < int_len; i++) {
    src.read(reinterpret_cast<char *>(&buffer), custom_size);
    input.push_back(buffer);
  }
  if(rem_len != 0) {
    src.read(reinterpret_cast<char *>(&buffer), rem_len);
    input.push_back(buffer);
  }
  src.close();

  for(auto i : input) {
    std::cout << i << std::endl;
    std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  }

  // DATA MANIPULATION HERE
  std::vector<int128_t> output(input.size(), 0);

  for(size_t i = 0; i < input.size(); i++) {
    // output[i] = input[i];
    output[i] = mod_pow_const_time_and_cond_copy(input[i], 91777883971757, 2107446121771421);
  }

  // WRITE TO ENCYPTED FILE
  std::string dstname = "tests2.bin";
  std::ofstream dst(dstname, std::ios::binary);

  for(size_t i = 0; i < int_len; i++) {
    buffer = output[i];
    dst.write(reinterpret_cast<const char *>(&buffer), custom_size);
  }
  if(rem_len != 0) {
    buffer = output.back();
    dst.write(reinterpret_cast<const char *>(&buffer), rem_len);
  }

  for(auto i : output) {
    std::cout << i << std::endl;
    std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  }

  dst.close();
}

#endif