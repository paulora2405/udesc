import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.util.*;
import java.io.*;

public class ChatServer implements ChatServerInterface {
  private static Integer clientID = 1;

  public ChatServer() {
  }

  public String setterName = null, arquivo = null;
  public int chatID = 0;

  /*
   * Salva em uma copia local o arquivo recebido
   */
  public void saveData() throws Exception {
    try {
      FileWriter output = new FileWriter(setterName + "-" + chatID + ".serv");

      output.write(arquivo);

      output.close();
    } catch (Exception ex) {
      throw new Exception(ex);
    }
  }

  public static void main(String[] args) {
    try {
      // System.setProperty("java.rmi.server.hostname", args[0]);

      ChatServer server = new ChatServer();
      ChatServerInterface stub = (ChatServerInterface) UnicastRemoteObject.exportObject(server, 0);

      Registry registry = LocateRegistry.createRegistry(6600);

      registry.bind("ChatRMI-Paulo", stub);
      System.out.println("Servidor pronto para conexões");

    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  /*
   * Retorna o chat anterior.
   */
  public List<String> getData() throws RemoteException {
    List<String> s = new ArrayList<String>();
    s.add(setterName);
    s.add(arquivo);
    return s;
  }

  /*
   * Recebe um arquivo do cliente.
   */
  public void setData(List<String> s) throws RemoteException {
    try {
      chatID++;
      setterName = s.get(0);
      arquivo = s.get(1);
      System.out.println("Chat de " + setterName + " recebido com sucesso.");
      saveData();
    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  public int getChatID() throws RemoteException {
    return chatID;
  }

  public int getClientID() throws RemoteException {
    return clientID++;
  }

  public String getSetter() throws RemoteException {
    return setterName;
  }
}
