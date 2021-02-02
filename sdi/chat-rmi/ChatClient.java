import java.rmi.registry.*;
import java.io.*;
import java.util.*;

public class ChatClient implements Runnable {
  static ChatServerInterface stub;
  private static Integer chatID = 0, clientID = null;
  private static boolean connected = false;
  public static Thread thr = null;
  static Registry registry;
  private static String host, clientName = null, conteudoArquivo;

  /*
   * Cria a copia local do arquivo recebido do servidor.
   */
  public static void writeChat(String fileName) throws Exception {
    try {
      FileWriter copiaLocal = new FileWriter(fileName);

      copiaLocal.write(conteudoArquivo);

      copiaLocal.close();

    } catch (Exception ex) {
      throw new Exception(ex);
    }
  }

  /*
   * Le o arquivo do chat local.
   */
  public static void readChat(String fileName) throws Exception {
    try {
      InputStream input = new FileInputStream(fileName);

      byte[] array = new byte[100000000];
      input.read(array);

      input.close();
      conteudoArquivo = new String(array);
      conteudoArquivo = conteudoArquivo.trim();
    } catch (Exception ex) {
      throw new Exception(ex);
    }
  }

  /*
   * Recebe o arquivo do servidor.
   */
  public static void receiveChat() throws Exception {
    try {
      init();

      int thisChatID = stub.getChatID();

      if (thisChatID != chatID) {
        String s = stub.getSetter();
        chatID = thisChatID;
        if (!s.equals(clientName) && s != null) {
          chatID = thisChatID;
          List<String> from = stub.getData();
          // from[1] é o conteudo do arquivo
          conteudoArquivo = from.get(1).trim();

          String fileName = new String(clientName + "-" + thisChatID + ".client" + clientID);
          writeChat(fileName);
          // from[0] é o nick do autor
          System.out.println("Chat de " + from.get(0) + " recebido com sucesso.");
        }
      }

    } catch (Exception ex) {
      throw new Exception(ex);
    }
  }

  /*
   * Funcao que envia o arquivo ja lido para o servidor.
   */
  public static void sendChat() throws Exception {
    try {
      init();
      List<String> s = new ArrayList<String>();
      s.add(clientName);
      s.add(conteudoArquivo);
      stub.setData(s);
      System.out.println("O arquivo foi enviado com sucesso!");
    } catch (Exception ex) {
      throw new Exception(ex);
    }
  }

  /*
   * Funcao faz uma comunicação de teste com o servidor.
   */
  public static void init() throws Exception {
    try {
      registry = LocateRegistry.getRegistry(host, 6600);

      stub = (ChatServerInterface) registry.lookup("ChatRMI-Paulo");
      if (!connected)
        System.out.println("Conectado com o servidor");
      connected = true;
    } catch (Exception ex) {
      connected = false;
      throw new Exception(ex);
    }
  }

  public static void setClientID() throws Exception {
    try {
      init();
      clientID = stub.getClientID();
    } catch (Exception ex) {
      throw new Exception(ex);
    }

  }

  /*
   * Funcao que gera o nickname do usuario e faz o polling automatico de arquivos.
   */
  public static void main(String[] args) {
    BufferedReader s = new BufferedReader(new InputStreamReader(System.in));

    host = (args.length < 1) ? null : args[0];
    System.out.println("Digite seu nickname abaixo");
    try {
      clientName = s.readLine();
    } catch (IOException e) {
      System.out.println("Falha na leitura do nickname");
      e.printStackTrace();
    }

    try {
      setClientID();
    } catch (Exception ex) {
      System.err.println("Houve uma falha na obtenção do ID");
      System.exit(0);
    }

    while (true) {
      try {
        receiveChat();
        if (thr == null) {
          thr = new Thread(new ChatClient());
          thr.start();
        }
      } catch (Exception ex) {
        System.err.println("Houve uma falha na conexão");
        System.exit(0);

      }
    }
  }

  /*
   * Função que responsavel pela leitura dos arquivos. OBS: é uma função executada
   * automaticamente quando se inicia a thread.
   */
  public void run() {
    BufferedReader s = new BufferedReader(new InputStreamReader(System.in));
    String fileName;
    while (true) {
      try {
        System.out.println("Digite o nome do arquivo com extensão abaixo");
        fileName = s.readLine();
        readChat(fileName);
        sendChat();
      } catch (Exception ex) {
        System.err.println("Erro ao enviar mensagem");
      }
    }
  }
}
