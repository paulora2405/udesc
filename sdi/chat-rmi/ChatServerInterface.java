import java.rmi.*;
import java.util.*;

public interface ChatServerInterface extends Remote {
   public List<String> getData() throws RemoteException;

   public void setData(List<String> s) throws RemoteException;

   public int getChatID() throws RemoteException;

   public int getClientID() throws RemoteException;

   public String getSetter() throws RemoteException;
}
