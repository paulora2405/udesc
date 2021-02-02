# Trabalho de Sistemas Distribuídos
 *Paulo Roberto Albuquerque* 

Instruções:
- Execute o comando `make`.
- Para o servidor, não há argumentos na execução, basta executar `./server`.
- Para os clientes, tem-se o seguinte formato: `./client <hostname>`, onde hostname é o server, `ens1` por exemplo.
- Siga as instruções impressas no terminal.

Funcionamento do cliente:
- Ao digitar o apelido, o servidor irá atribuir ao cliente um Id único para identificação.
- Pode-se selecionar a opção para enviar um arquivo, caso seja a escolha, deve-se digitar o nome do arquivo logo em seguida.
- Pode-se também selecionar a opção para receber um arquivo. OBS: Recebe-se apenas um arquivo por vez. 
- Quanto ao recebimento dos arquivos, três respostas do servidor são possíveis:
  - Não há novas mensagens.
  - Há uma nova mensagem, porém ela é de sua própria autoria, logo não será armazenada.
  - Há uma nova mensagem de outro cliente, e ela será armazenada no formato `<cliente>-<número do chat>.client<id único do cliente>`.
