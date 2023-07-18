package cum;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/** A demo RMI object is a server.
 * // st\nos5_b\out\production\nos5_b> start rmiregistry
 * */
public class Server implements Pi {

    public static void main(String args[]) {
        try {
            // Instantiate the remote object.
            Server obj = new Server();
            // Create a stub from it. The second argument is the port. If zero
            // then an anonymous (ephemeral) port is chosen. To ease firewall
            // config we can choose a specific port.
            Pi pi = (Pi) UnicastRemoteObject.exportObject(obj, 5000);

            // Get the registry and register the stub
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("PI", pi);

            System.out.println("Server running");
        }
        catch (Exception e) {
            System.out.println("Exception " + e);
            e.printStackTrace();
        }
    }

    @Override
    public double compute(int N) throws RemoteException {
        return 3.14 + uniform() + N;
    }

    @Override
    public double uniform() throws RemoteException {
        return Math.random();
    }
}
