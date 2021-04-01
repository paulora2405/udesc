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
 */
void encrypt_file(std::string src_path, std::string dst_path, struct Public_key pub_key) {
  using namespace boost::multiprecision;

  std::ifstream src(src_path, std::ios::in | std::ios::binary);
  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Ler arquivo original e colocar em uma string

  src.seekg(0, src.end);
  const long long len_file = src.tellg();
  src.seekg(0, src.beg);

  char *string_c = new char[len_file];
  src.read(string_c, len_file);
  src.close();

  // Transformar cada caracter da string em um inteiro

  long long *output = new long long[len_file];

  for(long long i = 0; i < len_file; i++) {
    output[i] = mod_pow_const_time_and_cond_copy(string_c[i], pub_key.e, pub_key.n);
  }
  delete[] string_c;

  std::ofstream dst(dst_path, std::ios::out | std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
  for(long long i = 0; i < len_file; i++) {
    dst.write(reinterpret_cast<const char *>(&output[i]), sizeof(output[0]));
  }

  delete[] output;
  dst.close();
}

/*
 * Decrypts a source file to a destination file.
 */
void decrypt_file(std::string src_path, std::string dst_path, struct Private_key priv_key) {
  std::ifstream src(src_path, std::ios::in | std::ios::binary);
  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Ler arquivo encriptado em inteiros

  src.seekg(0, src.end);
  const long long len_file = src.tellg();
  src.seekg(0, src.beg);

  long long *input = new long long[len_file / sizeof(long long)];

  for(unsigned long int i = 0; i < len_file / sizeof(long long); i++) {
    src.read(reinterpret_cast<char *>(&input[i]), sizeof(long long));
  }
  src.close();

  // Transformar cada inteiro em um char

  char *string_c = new char[len_file / sizeof(long long)];

  for(unsigned long int i = 0; i < len_file / sizeof(long long); i++) {
    string_c[i] = mod_pow_const_time_and_cond_copy(input[i], priv_key.d, priv_key.n);
  }
  delete[] input;

  // for(unsigned long int i = 0; i < strlen(string_c); i++) {
  //   std::cout << string_c[i];
  // }
  // std::cout << std::endl;

  std::ofstream dst(dst_path, std::ios::out | std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  dst.write(string_c, strlen(string_c));

  delete[] string_c;
  dst.close();
}

#endif