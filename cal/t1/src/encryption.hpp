#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "key_generator.hpp"

/*
 * Encrypts a source file to a destination file.
 */
void encrypt_file(std::string src_path, std::string dst_path) {
  std::ifstream src(src_path, std::ios::in | std::ios::binary);

  src.seekg(0, src.end);
  const long long len_file = src.tellg();
  src.seekg(0, src.beg);

  char *input = new char[len_file];

  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
  src.read(input, len_file);
  char *output = new char[len_file];

  for(long long i = 0; i < len_file; i++) {
    output[i] = input[len_file - i - 1] - 10;
  }
  std::ofstream dst(dst_path, std::ios::out | std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
  dst.write(output, len_file);

  delete input;
  delete output;
  src.close();
  dst.close();
}

/*
 * Decrypts a source file to a destination file.
 */
void decrypt_file(std::string src_path, std::string dst_path) {
  std::ifstream src(src_path, std::ios::in | std::ios::binary);

  src.seekg(0, src.end);
  const long long len_file = src.tellg();
  src.seekg(0, src.beg);

  char *input = new char[len_file];

  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
  src.read(input, len_file);
  char *output = new char[len_file];

  for(long long i = 0; i < len_file; i++) {
    output[i] = input[len_file - i - 1] + 10;
  }
  std::ofstream dst(dst_path, std::ios::out | std::ios::binary);
  if(!dst.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }
  dst.write(output, len_file);

  delete input;
  delete output;
  src.close();
  dst.close();
}

#endif