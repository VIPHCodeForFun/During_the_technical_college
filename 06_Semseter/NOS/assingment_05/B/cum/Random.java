package cum;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Random extends Remote {
    double uniform() throws RemoteException;
}
