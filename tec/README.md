## Trabalho Final - TEC
**Paulo Roberto Albuquerque**

### Sobre
No diretório do projeto, há um arquivo **diagramas.drawio**, que é um esboço do meu raciocínio para as partes mais complexas da conversão de DI para Sipser.

O programa também gera imagens de automatos finitos das máquinas de entrada e saída, para melhor visualização e também por curiosidade =)

As imagens dos grafos tem 2 formatos, _png_ e _svg_. Eu indico, porém, o _svg_ por se tratar de um formato vetorizado, que é bem mais leve para visualizar, e ampliar.

Também no diretório do projeto, há dois códigos de máquinas para testes, uma que gera infinitos 0's a direita e outra a esquerda (nesta, a entrada deve ser 00).


### Execução
Para compilar o programa:
```sh
$ make
```

Para rodar o programa:
```sh
$ ./main <NOME_DO_ARQUIVO>
```
A máquina convertida será escrita no arquivo **output.txt**.

Para gerar os grafos em _png_ e _svg_, que ficarão no diretório **dot/**:
```sh
$ make dot
```
A compilação das imagens de saída em formato _png_ podem demorar um pouco, mas é normal.

### Arquivos Fonte
O arquivo `main.cpp`, contém apenas o fluxo principal de arquivos de entrada e saída.

Em `aux_lib.hpp`, existem apenas algumas funções auxiliares.

O header `i_to_s.hpp` é responsável pela conversão de DI para Sipser.

O header `s_to_i.hpp` é responsável pela conversão de Sipser para DI, e possui algumas funções de auxílio para a conversão e manipulação das máquinas, que são usadas no header acima também, bem como algumas constantes e _typedefs_.

### Dependências

Para executar o programa em si, não há nenhuma dependência, porém, para criar as imagens geradas pelo GraphViz, é necessário a instalação do pacote do GraphViz.

No Ubuntu 20.04:
```sh
$ sudo apt install graphviz
```