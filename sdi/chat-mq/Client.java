import java.io.*;
import java.nio.file.Files;
import java.util.*;
import java.util.concurrent.ExecutionException;

import com.rabbitmq.client.*;

public class Client implements Runnable {
  private final static String queue_name = "Server-RabbitMQ";
  private static String tag = "";
  public static Thread thr = null;
  private static ConnectionFactory factory;
  private static Connection connection;
  private static Channel channel;
  private static Scanner input = new Scanner(System.in);

  public static void main(String[] args) throws Exception {
    factory = new ConnectionFactory();
    factory.setHost("localhost");
    connection = factory.newConnection();
    connection2 = factory.newConnection();
    channel = connection.createChannel();

    channel.queueDeclare(queue_name, false, false, false, null);
    System.out.println("Cliente inicializado com sucesso!\nAguardando mensagens...");

    System.out.print("Digite sua tag: ");
    tag = input.nextLine();
    String header = "##NEW##" + tag;
    channel.basicPublish("", queue_name, null, header.getBytes("UTF-8"));

    while (true) {
      if (thr == null) {
        thr = new Thread(new Client());
        thr.start();
      }

      Consumer consumer = new DefaultConsumer(channel) {
        @Override
        public void handleDelivery(String consumerTag, Envelope envelope, AMPQ.BasicProperties properties, byte[] body)
            throws IOException {
          String message = new String(body, "UTF-8");
          int index = message.indexOf("##ID##");
          String id = message.substring(0, index);
          message = message.substring(index + 6);
          index = message.indexOf("##TAG##");
          String tagSender = message.substring(0, index);
          message = message.substring(index + 7);
          System.out.println(tagSender + "enviou um chat!");
          receiveFile(tag, tagSender, message);
        }
      };
      channel.basicConsume(tag, true, consumer);
    }
    channel.queueDeclare(queue_name);
    channel.close();
    connection.close();
  }

  public static String sendFile(String path) {
    try {
      InputStream is = new FileInputStream(path);
      byte[] bytes = new byte[65536];
      is.read(bytes);
      is.close();
      return new String(bytes);
    } catch (Exception e) {
      throw new Exception(e);
    }

  }

  public static void receiveFile(String recvTag, String sendTag, String message) {
    try {
      String path = recvTag + "-client";
      new File(path).mkdir();
      FileWriter fw = new FileWriter(path + "/" + sendTag + "-" + id + ".client");
      fw.write(message);
      fw.close();
    } catch (Exception e) {
      return;
    }
  }

  public void run() {
    while (true) {
      System.out.println("Digite o nome do arquivo do chat a ser enviado (com a extensão):");
      String path = input.nextLine();
      String message = sendFile(path);
      channel.basicPublish("", queue_name, null, message.getBytes("UTF-8"));
    }
  }

}
