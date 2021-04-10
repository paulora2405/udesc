#include "../include/key_generator.hpp"

Key_pair initialize_128(unsigned max_bits, bool print) {
  if(max_bits > 256) {
    throw std::runtime_error("Tamanho de chave não suportada\n");
  }
  big_int p, q, n, totn, e, d, tmp;
  Prime_generator gen(std::time(NULL));

  // Passo 1: Selecionar dois numeros primos aleatorios grandes p e q
  // Passo 2: Calcular n = p * q
  // Passo 3
  // Passo 4: Achar um e tal que gcd(e, ø(n)) = 1 ; 1 < e < ø(n)
  // Passo 5: Calcular d tal que e*d = 1 (mod ø(n))

  do {
    p = gen.random_prime(max_bits / 2);
    q = gen.random_prime(max_bits / 2);

    n = p * q;
    totn = (p - 1) * (q - 1);

    do {
      e = gen.random_prime(max_bits);
    } while(e >= totn);

    euclides_extended(e, totn, d, tmp);
    d = (d % totn + totn) % totn;

  } while((e * d % totn) != 1);

  // Imprimir os resultados
  if(print) {
    std::cout << "Max bits for N: " << max_bits << std::endl;
    std::cout << "The values calculated were:" << std::endl;
    std::cout << "P = " << p << std::endl;
    std::cout << "Q = " << q << std::endl;
    std::cout << "N = " << n << std::endl;
    std::cout << "Tot(N) = " << totn << std::endl;
    std::cout << "E = " << e << std::endl;
    std::cout << "D = " << d << std::endl;
  }

  Key pub = {e, n};
  Key priv = {d, n};
  Key_pair pair = {pub, priv};

  return pair;
}
