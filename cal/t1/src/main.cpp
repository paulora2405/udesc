#include <iostream>
#include <string>

#include "encryption.hpp"
#include "file_manipulation.hpp"
#include "key_generator.hpp"
#include "mod_exponentiation.hpp"

int main(int argc, char const *argv[]) {
  // o nome do arquivo será passado via parametro
  if(argc != 1) {
    std::cerr << "Quantidade de argumentos errada" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string texto = "Este é um texto de teste!";

  write_file("original.bin", texto);

  // valores maiores que este quebram a criptografia
  struct Key_pair keys = initialize_ll(1000, 10000);
  encrypt_file("original.bin", "encriptado.bin", keys.pub_key);
  decrypt_file("encriptado.bin", "decriptado.bin", keys.priv_key);

  print_file("original.bin");
  print_file("encriptado.bin");
  print_file("decriptado.bin");
}
