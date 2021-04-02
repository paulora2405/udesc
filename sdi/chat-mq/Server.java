import java.io.*;
import java.util.*;
import com.rabbitmq.client.*;

public class Server {
  private final static List<String> queue_names = new ArrayList<String>();
  private static ConnectionFactory factory;
  private static Connection connection;
  private static Channel channel;
  public static int id = 0;

  public static void main(String[] argv) throws Exception {
    factory = new ConnectionFactory();
    factory.setHost("localhost");
    connection = factory.newConnection();
    channel = connection.createChannel();
    queue_names.add("Server-RabbitMQ");

    channel.queueDeclare(queue_names.get(0), false, false, false, null);
    System.out.println("Servidor inicializado com sucesso!\nAguardando mensagens...");

    Consumer consumer = new DefaultConsumer(channel) {
      @Override
      public void handleDelivery(String consumerTag, Envelope envelope, AMQP.BasicProperties properties, byte[] body)
          throws IOException {
        String message = new String(body, "UTF-8");

        if (message.startsWith("##NEW##")) {
          String name = message.substring(7);
          queue_names.add(name);
          Channel aux;
          aux = connection.createChannel();
          aux.queueDeclare(queue_names.get(queue_names.size() - 1), false, false, false, null);
          System.out.println(queue_names.get(queue_names.size() - 1) + " conectou-se ao chat!");
        } else {
          id++;
          int index = message.indexOf("##TAG##");
          String tag = message.substring(0, index);
          System.out.println(tag + " enviou um chat!");
          receiveFile(tag + "-" + id + "serv", message.substring(index + 7));
          message = id + "##ID##" + message;
          sendFile(message, tag);
        }
      }
    };

    while (true) {
      try {
        channel.basicConsume(queue_names.get(0), true, consumer);
      } catch (Exception e) {
        break;
      }
    }
    channel.close();
    connection.close();
  }

  public static void sendFile(String message, String tag) {
    for (int i = 1; i < queue_names.size(); i++) {
      try {
        String name = queue_names.get(i);
        if (tag.compareTo(name) == 0)
          continue;
        channel.queueDeclare(name, false, false, false, null);
        channel.basicPublish("", name, null, message.getBytes("UTF-8"));
      } catch (Exception e) {
        continue;
      }
    }
  }

  public static void receiveFile(String filename, String message) {
    try {
      String path = "Server";
      new File(path).mkdir();
      FileWriter fw = new FileWriter(path + "/" + filename);
      fw.write(message);
      fw.close();
    } catch (Exception e) {
      return;
    }
  }
}
