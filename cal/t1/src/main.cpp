#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

#include "big_int_type.hpp"
#include "encryption.hpp"
#include "file_manipulation.hpp"
#include "key_generator.hpp"
#include "tests.hpp"

void test_encryption() {
  // std::string texto = "abcdefghijklmnopqrstuvwxyz";
  // std::string texto = "abcdef";
  // write_file("original.bin", texto);
  big_int upp(1);
  upp = (upp << 127) - 1;
  struct Key_pair keys = initialize_128(upp, true);
  // encrypt_file("original.bin", "encriptado.bin", keys.pub_key);
  // decrypt_file("encriptado.bin", "decriptado.bin", keys.priv_key);

  // print_file("original.bin");
  // print_file("encriptado.bin");
  // print_file("decriptado.bin");
}

int main(int argc, char const *argv[]) {
  using namespace boost::multiprecision;
  // o nome do arquivo será passado via parametro
  if(argc != 1) {
    std::cerr << "Quantidade de argumentos errada" << std::endl;
    exit(EXIT_FAILURE);
  }

  test_encryption();

  // int_limits();
}
