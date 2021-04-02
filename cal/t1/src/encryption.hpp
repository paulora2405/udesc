#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "key_generator.hpp"
#include "mod_exponentiation.hpp"

/*
 * Encrypts a source file to a destination file.
 if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
 */
void encrypt_file(std::string src_path, std::string dst_path, struct Public_key pub_key) {
  using namespace boost::multiprecision;

  // READ FROM OG FILE
  std::ifstream src(src_path, std::ios::binary);
  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  int128_t buffer;
  std::vector<int128_t> input;

  /*
  40 / 32 = 1
  len_file / sizeof(uint128_t)
  40 % 32 = 8
  len_file % sizeof(uint128_t)
  */
  src.seekg(0, src.end);
  size_t custom_size = sizeof(int128_t) / 2;
  size_t len_file = src.tellg();
  size_t int_len = len_file / custom_size;
  size_t rem_len = len_file % custom_size;
  src.seekg(0, src.beg);

  // std::cout << "Len_file (bytes): " << len_file << std::endl;
  // std::cout << "Int_len (blocks): " << int_len << std::endl;
  // std::cout << "Rem_len (bytes): " << rem_len << std::endl;

  for(size_t i = 0; i < int_len; i++) {
    src.read(reinterpret_cast<char *>(&buffer), custom_size);
    input.push_back(buffer);
  }
  if(rem_len != 0) {
    src.read(reinterpret_cast<char *>(&buffer), rem_len);
    input.push_back(buffer);
  }
  src.close();

  // DATA MANIPULATION HERE
  std::vector<int128_t> output(input.size(), 0);

  for(size_t i = 0; i < input.size(); i++) {
    // output[i] = input[i] + 1;
    output[i] = mod_pow_const_time_and_cond_copy(input[i], pub_key.e, pub_key.n);
  }

  // TESTS
  // for(auto i : input) {
  //   std::cout << i << std::endl;
  //   std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  // }
  // for(auto i : output) {
  //   std::cout << i << std::endl;
  //   std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  // }

  // WRITE TO ENCYPTED FILE
  std::ofstream dst(dst_path, std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  for(size_t i = 0; i < int_len; i++) {
    buffer = output[i];
    dst.write(reinterpret_cast<const char *>(&buffer), custom_size);
  }
  if(rem_len != 0) {
    buffer = output.back();
    int n = 0;
    while(buffer != 0) {
      buffer >>= 8;
      n++;
    }
    buffer = output.back();
    dst.write(reinterpret_cast<const char *>(&buffer), n);
  }

  dst.close();
}

/*
 * Decrypts a source file to a destination file.
 */
void decrypt_file(std::string src_path, std::string dst_path, struct Private_key priv_key) {
  using namespace boost::multiprecision;

  // READ FROM OG FILE
  std::ifstream src(src_path, std::ios::binary);
  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  int128_t buffer;
  std::vector<int128_t> input;

  /*
  40 / 32 = 1
  len_file / sizeof(uint128_t)
  40 % 32 = 6
  len_file % sizeof(uint128_t)
  */
  src.seekg(0, src.end);
  size_t custom_size = sizeof(int128_t) / 2;
  size_t len_file = src.tellg();
  size_t int_len = len_file / custom_size;
  size_t rem_len = len_file % custom_size;
  src.seekg(0, src.beg);

  // std::cout << "Len_file (bytes): " << len_file << std::endl;
  // std::cout << "Int_len (blocks): " << int_len << std::endl;
  // std::cout << "Rem_len (bytes): " << rem_len << std::endl;

  for(size_t i = 0; i < int_len; i++) {
    src.read(reinterpret_cast<char *>(&buffer), custom_size);
    input.push_back(buffer);
  }
  if(rem_len != 0) {
    src.read(reinterpret_cast<char *>(&buffer), rem_len);
    input.push_back(buffer);
  }
  src.close();

  // DATA MANIPULATION HERE
  std::vector<int128_t> output(input.size(), 0);

  for(size_t i = 0; i < input.size(); i++) {
    // output[i] = input[i] - 1;
    output[i] = mod_pow_const_time_and_cond_copy(input[i], priv_key.d, priv_key.n);
  }

  // TESTS
  // for(auto i : input) {
  //   std::cout << i << std::endl;
  //   std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  // }
  // for(auto i : output) {
  //   std::cout << i << std::endl;
  //   std::cout << reinterpret_cast<const char *>(&i) << std::endl;
  // }

  // WRITE TO ENCYPTED FILE
  std::ofstream dst(dst_path, std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  for(size_t i = 0; i < int_len; i++) {
    buffer = output[i];
    dst.write(reinterpret_cast<const char *>(&buffer), custom_size);
  }
  if(rem_len != 0) {
    buffer = output.back();
    int n = 0;
    while(buffer != 0) {
      buffer >>= 8;
      n++;
    }
    buffer = output.back();
    dst.write(reinterpret_cast<const char *>(&buffer), n);
  }

  dst.close();
}

#endif