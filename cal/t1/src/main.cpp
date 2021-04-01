#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

// #include "encryption.hpp"
#include "file_manipulation.hpp"
#include "key_generator.hpp"
#include "tests.hpp"

int main(int argc, char const *argv[]) {
  using namespace boost::multiprecision;
  // o nome do arquivo será passado via parametro
  if(argc != 1) {
    std::cerr << "Quantidade de argumentos errada" << std::endl;
    exit(EXIT_FAILURE);
  }

  // std::string texto = "Este é um texto de teste!";
  // write_file("original.bin", texto);
  // valores maiores que este quebram a criptografia
  // struct Key_pair keys = initialize_128(2432902008176640000);
  // encrypt_file("original.bin", "encriptado.bin", keys.pub_key);
  // decrypt_file("encriptado.bin", "decriptado.bin", keys.priv_key);

  // print_file("original.bin");
  // print_file("encriptado.bin");
  // print_file("decriptado.bin");

  // test file int128
  // encrypt_test();

  // 74719769323023431933 quebra
  // 5360825248451044571 nao quebra
  // 9805467456659889323 nq
  // 37633746138219895883 q
  // 5774889990524933347 nq
  // 24,290,033,684,151,547,057 q
  //  9,223,372,036,854,775,807 maior signed long long
  // 18,446,744,073,709,551,615 maior unsigned long long
  // test negative mod pow
  struct Key_pair keys = initialize_128(100000000LL);
  // struct Key_pair keys = initialize_128(9223372036854775807LL);
  int128_t enc = mod_pow_const_time_and_cond_copy(-500, keys.pub_key.e, keys.pub_key.n);
  std::cout << std::endl << enc << std::endl;
  std::cout << mod_pow_const_time_and_cond_copy(enc, keys.priv_key.d, keys.priv_key.n) << std::endl;
}
