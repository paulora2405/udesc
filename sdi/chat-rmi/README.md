# Trabalho de Sistemas Distribuídos
 *Paulo Roberto Albuquerque* 

Instruções:
- Execute o comando `make`.
- Para o servidor, não há argumentos na execução, basta executar `java ChatServer`.
- Para os clientes, tem-se o seguinte formato: `java ChatClient <hostname>`, onde hostname é o server, `ens2` por exemplo.
- Siga as instruções impressas no terminal.

Funcionamento do cliente e servidor:
- Ao digitar o apelido, o servidor irá atribuir ao cliente um Id único para identificação.
- Para enviar um arquivo basta digitar o nome do arquivo (com extensão), conforme a instrução no terminal. Ex: para um arquivo chamado `test.chat` deve ser digitado `test.chat` no terminal.
- O recebimento de arquivos é feito de maneira automátiva. 
- Quanto ao recebimento dos arquivos do servidor, estes serão armazenados no formato `<cliente>-<número do chat>.client<id único do cliente>`.
- O servidor criará cópias locais dos arquivos no formato `<autor>-<número do chat>.serv`.
- Para gerar os arquivos de 1KB e 1MB, use `base64 /dev/urandom | head -c 1K > file1K.txt` ou `base64 /dev/urandom | head -c 1M > file1M.txt`.
- Para conferir se os arquivos são idênticos basta executar `diff arquivo1 arquivo2`.
- O servidor deve ser executado no `ens2` para evitar problemas de comportamento imprevisível.
- Todos os cenários foram testados mútiplas vezes e funcionaram 100%.