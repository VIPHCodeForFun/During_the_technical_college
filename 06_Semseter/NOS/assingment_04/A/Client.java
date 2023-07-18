package A;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Client {

    /* Properties */
    private Socket clientSocket = null;

    /** A PrinterWriter that wraps around the sockets output stream. */
    private PrintWriter clientOut = null;
    /** A BufferedReader that wraps around the socket input stream. */
    private BufferedReader clientIn = null;

    private Thread listeningThread = null;

    /* Methods */
    public void writeLineToServer(String message) {
        try {
            /* Sending a message to the server */
            clientOut.println(message);
            clientOut.flush();
        } catch (Exception e) {
            System.out.println("[Client] Error writeLineToServer(): " + e.getMessage());
        }
    } /* writeLineToServer() */

    public void startListening() {
        listeningThread = new Thread(new Runnable() {
            @Override
            public void run() {
                String message;
                try {
                    while (!Thread.currentThread().isInterrupted()) {
                        /* Receiving a message from the server */
                        message = clientIn.readLine();
                        if (message != null) {
                            System.out.println("[Client] from Server: '" + message + "'");
                        }
                        if (clientSocket.isConnected() == false) {
                            System.out.println("disconnected");
                        }
                    } /* end While */
                } catch (Exception e) {
                    System.out.println("[Client][Thread] shutdown ");
                }
            } /* run() */
        }); /* Thread() */
        listeningThread.start();
    } /* startListening() */

    public void start() {
        try {
            System.out.println("[Client] Start client on localhost:5000");
            this.clientSocket = new Socket("localhost", 5000);
            System.out.println("[Client] Connected with server");
            this.clientOut = new PrintWriter(clientSocket.getOutputStream(), true);
            this.clientIn = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        } catch (Exception e) {
            System.out.println("[Client] Error start(): " + e.getMessage());
        }
    } /* start() */

    public void close() {
        try {
            if (this.listeningThread != null)
                this.listeningThread.interrupt();
            /*
             * ! Step program gets stuck don't want to take advantage of it !
             * https://i.kym-cdn.com/photos/images/original/001/911/736/d4a.jpg
             * if (this.clientIn != null)
             * this.clientIn.close();
             * if (this.clientOut != null)
             * this.clientOut.close();
             */
            if (this.clientSocket != null)
                this.clientSocket.close();

        } catch (Exception e) {
            System.out.println("[Client] Error: shutDown()" + e.getMessage());
        }
    } /* shutDown() */

    /*-MAIN-------------------------------------------------------------------*/
    public static void main(String[] args) throws Exception {
        System.out.println("[Client] -------------------------------");
        System.out.println("[Client] -! Type 'exit' to shut down !-");
        Client client = new Client();
        Scanner scanner = new Scanner(System.in);
        try {
            client.start();
            client.startListening();

            /* Chat to Server */
            String message = "null";
            while (true) {
                message = scanner.nextLine();
                client.writeLineToServer(message);
                if (message.equals("exit")) {
                    scanner.close();
                    break;
                }
            }
        } finally {
            client.close();
            System.out.println("[Client] Good by.");
        }
    }
}
