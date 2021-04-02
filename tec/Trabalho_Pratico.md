### Anotações

##### Para transformar uma MT com fita DI para Sipser:

1. Ao inicio da execução, move o cabeçote para a direita e marca com um símbolo especial, delimitando a fita para a esquerda.
1. Sempre que o cabeçote fizer um movimento para a esquerda, verificar se a célula contém o símbolo especial.
    1. Se sim, movimentar novamente para a direita e continuar a execução.

##### Para transformar uma MT Sipser para DI:



---

### Enunciado
O objetivo deste trabalho é demonstrar a equivalência de duas variantes disponíveis no simulador online de máquinas de Turing em http://morphett.info/turing/turing.html

Mais especificamente: será possível notar que a variante de fita duplamente infinita e a variante de fita semi-infinita (modelo de Sipser) podem simular uma à outra.


O trabalho consistirá em um programa que receberá um arquivo txt com uma entrada para o simulador, onde a primeira linha será

- `;I`

caso seja um programa para máquina de Turing com fita duplamente infinita

- `;S`

caso seja um programa para máquina de Turing com fita semi-infinita (modelo de Sipser)

O restante do arquivo será constituído exclusivamente de linhas no formato

`<current state> <current symbol> <new symbol> <direction> <new state>`

conforme especificado no site do simulador, sem uso de novos comentários.
Tem-se a garantia de que os símbolos `£`,`¢`,`§` não serão utilizados em nenhum arquivo de entrada, podendo ser utilizados como eventuais símbolos auxiliares.

O programa deverá retornar como saída um arquivo txt com um programa equivalente para o simulador online com tipo de fita inverso ao indicado no arquivo de entrada.

Os arquivos de entrada serão apenas de máquinas de Turing determinísticas e com codificação válida para o simulador. Todos os programas dados como entrada serão para reconhecimento de linguagens sobre o alfabeto {0,1}. Note, portanto, que a máquina de Turing dada como saída também será um reconhecedor para essa mesma linguagem sobre o alfabeto {0,1}.

O programa deve ser possível de ser executado em um computador com sistema operacional Ubuntu 20.04.2 LTS de 64 bits. A linguagem de implementação é livre dentro destas restrições.

A entrega deverá ser feita via moodle, com o <u>programa final</u>, <u>instruções claras de execução</u> caso necessárias e <u>endereço de repositório público no github com todo o código-fonte</u>.


