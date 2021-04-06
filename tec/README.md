## Trabalho Final - TEC
**Paulo Roberto Albuquerque**

### Dependências

Para executar o programa em si, não há nenhuma dependência, porém, para criar as imagens geradas pelo GraphViz, é necessário a instalação do pacote do GraphViz.
No Ubuntu 20.04:
```sh
$ sudo apt install graphviz
```

### Execução
Para compilar o programa:
```sh
$ make
```

Para rodar o programa:
```sh
$ ./main <NOME_DO_ARQUIVO>
```

Para gerar os grafos em _png_ e _svg_, que ficarão no diretório **dot/**:
```sh
$ make dot
```