import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import cum.Pi;

/** An RMI client demo of a remote Calculator object. */
class RMIClient {
    public static void main(String args[]) {
        // Host is either default on TCP port localhost:1099 or given by
        // args[0].
        String host = null;
        if (args.length >= 1)
            host = args[0];

        try {
            // Connect to the rmiregistry and look up the calculator
            Registry registry = LocateRegistry.getRegistry(host);
            Pi pi = (Pi) registry.lookup("PI");

            // Some test calls on the calculator
            double pI = pi.compute(5);
            System.out.println("pi = " + pI);
        }
        catch (Exception e) {
            System.out.println("Exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
