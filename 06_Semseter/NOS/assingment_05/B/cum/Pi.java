package cum;

import java.rmi.RemoteException;

public interface Pi extends Random{

    double compute(int N) throws RemoteException;

}
