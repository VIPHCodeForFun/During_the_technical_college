
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Server implements Runnable {

    /* Properties */
    private ServerSocket server = null;
    private List<ServerSockets> socketList = null;
    private int serverPort = 0;

    /* Constructor */
    Server(int port) {
        this.serverPort = port;
        this.socketList = new ArrayList<ServerSockets>();
    }

    /* Methods */
    /** Start Server */
    @Override
    public void run() {
        try {
            server = new ServerSocket(this.serverPort);
            int sockedID = 0;
            while (!Thread.currentThread().isInterrupted()) {
                /* Wait for new client */
                System.out.println("[Server] Wait for new client...");
                Socket incoming = server.accept();
                ServerSockets socket = new ServerSockets(incoming, sockedID);
                /* Add new Client to server vector */
                socketList.add(socket);
                System.out.println("[Server] Socked[" + sockedID + "] is connected with client");
                /* Start socked listening thread */
                System.out.println("[Server] Socket thread started [" + sockedID + "]");
                /* Send Server ID to new client */
                writeLineToClient(sockedID, "ServerID|" + sockedID + "|");
                sockedID++;
            }
        } catch (Exception e) {
            System.out.println("[Server][Thread] shutdown " + e.getMessage());
        }
    }

    /** Shut down Server */
    void close() {
        try {
            /* Close all Sockets List<ServerSockets> socketList */
            for (int index = 0; index < socketList.size(); index++) {
                if (socketList.get(index) != null) {
                    socketList.get(index).close();
                }
                socketList.remove(index);
            }
            /* Close server */
            if (server != null)
                server.close();
        } catch (Exception e) {
            System.out.println("[Server] Error closing elements" + e.getMessage());
        } finally {
            System.out.println("[Server] Wait for Clients to shut down...");
        }
    } /* close() */

    public void writeLineToClient(int sockedID, String message) {
        try {
            ServerSockets socket = findSocket(sockedID, this.socketList);
            if (socket != null) {
                /* Sending a message to the server */
                socket.serverOut.println(message);
                socket.serverOut.flush();
            }
        } catch (Exception e) {
            System.out.println("[Server] Error writeLineToClient(" + sockedID + ",message): " + e.getMessage());
        }
    } /* writeLineToClient(int sockedID, String message) */

    public ServerSockets findSocket(int sockedID, List<ServerSockets> socketList) {
        for (ServerSockets serverSocket : socketList) {
            if (serverSocket.sockedID == sockedID) {
                return serverSocket;
            }
        }
        return null;
    } /* findSocket(int sockedID, List<ServerSockets> socketList) */

    /*-MAIN-------------------------------------------------------------------*/
    public static void main(String[] args) throws Exception {
        System.out.println("[Server] -------------------------------");
        System.out.println("[Server] -! Type 'close' to exit down !-");
        Server server = new Server(5000);
        Thread serverThread = new Thread(server);
        serverThread.start();

        Scanner scanner = new Scanner(System.in);
        String message = "null";
        while (true) {
            message = scanner.nextLine();
            if (message.equals("exit")) {

                scanner.close();
                break;
            }
        }
        scanner.close();

        server.close();
        serverThread.interrupt();
    } /* public static void main(String[] args) */
}
