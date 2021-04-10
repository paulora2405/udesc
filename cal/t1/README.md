# Trabalho de Complexidade de Algoritmos 2020-2
*Paulo Roberto Albuquerque & Menderson Costa*

---

### Geração da chave pública e privada
1. Selecionar dois números primos aleatorios `p` e `q`
1. Calcular `n = p * q`
1. Calcular `ø(n) = (p - 1)*(q - 1)`
1. Achar um `e` tal que `gcd(e, ø(n)) = 1 ; 1 < e < ø(n)`
1. Calcular `d` tal que `e*d = 1 (mod ø(n))`

- A chave Pública será `(n, e)`
- A chave Privada será `(n, d)`

### Encriptação e Decriptação
Dada uma mensagem `m` e uma mensagem cifrada `c`

##### Encriptação
- Dada uma mensagem `m` usar <code>m<sup>e</sup> = c (mod n)</code> para calcular a mensagem cifrada `c`

##### Decriptação
- Dada uma mensagem cifrada `c` usar <code>c<sup>d</sup> = m (mod n)</code> para calcular a mensagem original

### Bibliotecas de funções

##### `encryption.hpp`
- `void encrypt_file(string src_path, string dst_path, Public_key pub_key)`
  - Função para encriptar um arquivo usando uma chave pública.
- `void decrypt_file(string src_path, string dst_path, Private_key priv_key)`
  - Função para decriptar um arquivo usando uma chave privada.

##### `euclidean.hpp`
- `long long gcd(long long a, long long b)`
  - Função do algoritmo euclidiano recursivo para calcular o Máximo Divisor Comum.
- `long longong long gcd_iter(long long num1, long long num2)`
  - Função do algoritmo euclidiano iterativo para calcular o MDC
- `long long euclides_extended(long long m, long long n, long long *a, long long *b)`
  - Função do algoritmo euclidiano estendido para calcular o MDC e os coeficientes da Identidade de Bézout.

##### `file_manipulation.hpp`
- `void print_file(string file_name)`
  - Função para ler o conteúdo de um arquivo e imprimir no console.
- `void write_file(string file_name, string content)`
  - Função para escrever conteúdo em um arquivo.

##### `key_generator.hpp`
- `long long get_e_value(long long phin)`
  - Função para calcular um valor de `e` válido.
- `void print_keys(long long &p, long long &q, long long &n, long long &phin, long long &e, long long &d)`
  - Função para imprimir as chaves e valores auxiliares.
- `Key_pair initialize_ll(long long lowerbound, long long upperbound)`
  - Função para gerar os valores de `p`, `q`, `n`, `Phi(n)`, `e`, `d`.

##### `mod_exponentiation.hpp`
- `long long mod_pow_fast(long long base, long long power, long long n)`
  - Função de potenciação modular rápida.
- `long long mod_pow_const_time(long long base, long long power, long long n)`
  - Função de potenciação modular com tempo constante.
- `long long mod_pow(long long base, long long power, long long n)`
  - Função de potenciação modular com tempo constante e cópia condicional.

##### `primality.hpp`
- `bool is_composite(long long n, long long a, long long d, int s)`
  - Função para verificar se um número é composto.
- `bool miller_rabin(long long n)`
  - Função para verificar primalidade usando o algoritmo de Miller-Rabin.
- `long long random_prime(long long lowerbound, long long upperbound)`
  - Função que gera um primo aleatório dentro de um determinado intervalo.

##### `random_generator_seed.hpp`
- `std::default_random_engine generator(seed);`
  - Gerador de números aleatórios.
- `std::random_device myRandomDevice;` `unsigned int seed = myRandomDevice();`
  - Semente usada no gerador.

---

### Problemas não resolvidos
- Um número com magnitude maior que `1000000000` no valor `n` das chaves quebra as funções de cripografia.

##### Possíveis soluções
- A pesquisar

### Observações do Professor
- Nos graficos, não usar escala logarítmica.

### Links importantes
- Paper sobre implementação de RSA em C
  - https://www.academia.edu/40465824/RSA_Implementation_using_C_

- Documentação sobre a bibli de inteiros grandes *gmp*
  - https://gmplib.org/manual/Integer-Functions

- Implementação de RSA em C++
  - https://www.tutorialspoint.com/cplusplus-program-to-implement-the-rsa-algorithm

- Wiki sobre testes de primalidade
  - https://en.wikipedia.org/wiki/Primality_test

- Algoritimos do brute para testes de primalidade
  - https://github.com/BRUTEUdesc/AlmanaqueBrute/tree/master/Matem%C3%A1tica/Primos

- Exemplo RSA em Java
  - https://stackoverflow.com/questions/15920739/rsa-implementation-using-java

- Long long e biblioteca de inteiros customizados
  - https://stackoverflow.com/questions/6462439/whats-the-difference-between-long-long-and-long

- Algoritmo de euclides estendido
  - https://www.ime.usp.br/~coelho/mac0338-2004/aulas/mdc/index.html

- Calculadora rsa
  - https://www.cs.drexel.edu/~jpopyack/IntroCS/HW/RSAWorksheet.html

- RSA prático
  - https://www.cs.drexel.edu/~jpopyack/Courses/CSP/Fa17/notes/10.1_Cryptography/RSA_Express_EncryptDecrypt_v2.html