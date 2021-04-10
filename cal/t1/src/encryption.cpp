#include "../include/encryption.hpp"

unsigned log_b(big_int n) {
  unsigned b{0};
  while(n) {
    n >>= 1;
    b++;
  }
  return b;
}

/*
 * Data manipulation algorithm.
 */
void data_manipulation(std::string src_path, std::string dst_path, Key key) {
  using namespace boost::multiprecision;

  // READ FROM ORIGINAL FILE
  std::ifstream src(src_path, std::ios::binary);
  if(!src.is_open()) {
    std::cerr << "Arquivo não pode ser aberto com sucesso" << std::endl;
    exit(EXIT_FAILURE);
  }

  const unsigned BLOCK_SIZE = log_b(key.n) - 1;
  big_int buffer;
  std::vector<big_int> input;

  /*
  40 / 32 = 1
  len_file / sizeof(uint128_t)
  40 % 32 = 8
  len_file % sizeof(uint128_t)
  */
  src.seekg(0, src.end);
  size_t custom_size = BLOCK_SIZE;
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
  std::vector<big_int> output(input.size(), 0);

  for(size_t i = 0; i < input.size(); i++) {
    output[i] = mod_pow(input[i], key.d_e, key.n);
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

  // WRITE TO MANIPULATED FILE
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
    do {
      buffer >>= 8;
      n++;
    } while(buffer != 0);
    buffer = output.back();
    dst.write(reinterpret_cast<const char *>(&buffer), n);
  }

  dst.close();
}

/*
 * Encrypts a source file to a destination file.
 */
void encrypt_file(std::string src_path, std::string dst_path, Key pub_key) {
  data_manipulation(src_path, dst_path, pub_key);
}

/*
 * Decrypts a source file to a destination file.
 */
void decrypt_file(std::string src_path, std::string dst_path, Key priv_key) {
  data_manipulation(src_path, dst_path, priv_key);
}
