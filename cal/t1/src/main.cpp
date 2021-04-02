#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

#include "encryption.hpp"
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

  // std::string texto = "abcdefghijklmnopqrstuvwxyz";
  std::string texto = "abcdef";
  write_file("original.bin", texto);
  struct Key_pair keys = initialize_128(10000000000000LL, false);
  encrypt_file("original.bin", "encriptado.bin", keys.pub_key);
  decrypt_file("encriptado.bin", "decriptado.bin", keys.priv_key);

  // print_file("original.bin");
  // print_file("encriptado.bin");
  // print_file("decriptado.bin");

  // encrypt_test();

  // 74719769323023431933 quebra
  // 174826128581491075408507 NAO ESTA MAIS QUEBRANDO COM ESTE NUMERO
  // 5360825248451044571 nao quebra
  // 24,290,033,684,151,547,057 quebra (20 algarismos)
  //  9,223,372,036,854,775,807 maior signed long long
  // 18,446,744,073,709,551,615 maior unsigned long long

  // The values calculated were:
  // P = 12207809
  // Q = 4592683
  // N = 56066596861547
  //     112585661964897
  // Phi(N) = 56066580061056
  // E = 170217850973
  // D = 24811004278901
  // int128_t a(112585661964897);
  // std::cout << a << std::endl;
  // int128_t enc = mod_pow_const_time_and_cond_copy(a, 170217850973, 56066596861547);
  // std::cout << enc << std::endl;
  // std::cout << mod_pow_const_time_and_cond_copy(enc, 24811004278901, 56066596861547) <<
  // std::endl;
}
