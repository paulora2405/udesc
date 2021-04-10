#include <iostream>

#include "../include/key_generator.hpp"

void test_encryption() {
  // std::string texto = "abcdefghijklmnopqrstuvwxyz";
  // std::string texto = "abcdef";
  // write_file("original.bin", texto);
  Key_pair keys = initialize_128(100, true);
  keys.priv_key = keys.priv_key;  // só pro compilador nao encher o saco
  // encrypt_file("original.bin", "encriptado.bin", keys.pub_key);
  // decrypt_file("encriptado.bin", "decriptado.bin", keys.priv_key);

  // print_file("original.bin");
  // print_file("encriptado.bin");
  // print_file("decriptado.bin");
}

int main() {
  using namespace boost::multiprecision;

  test_encryption();
}
