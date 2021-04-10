#include <iostream>

#include "../include/key_generator.hpp"

void test_encryption() {
  // std::string texto = "abcdefghijklmnopqrstuvwxyz";
  // std::string texto = "abcdef";
  // write_file("original.bin", texto);
  Key_pair keys = initialize_128(100, true);

  char c = 'a';
  big_int c_num = (int)c;
  std::cout << "C_num: " << c_num << '\n';
  big_int enc = mod_pow(c_num, keys.pub_key.d_e, keys.pub_key.n);
  std::cout << "Enc antes: " << enc << '\n';
  enc = mod_pow(enc, keys.priv_key.d_e, keys.priv_key.n);
  std::cout << "Enc depois: " << enc << '\n';

  if(c_num != enc) std::cout << "Nao foi igual" << std::endl;
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
