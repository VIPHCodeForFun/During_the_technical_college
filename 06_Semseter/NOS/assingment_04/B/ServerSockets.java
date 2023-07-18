import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Vector;

public class ServerSockets {
    /* Properties */
    /** A BufferedReader that wraps around the socket input stream. */
    public BufferedReader serverIn = null;
    /** A PrinterWriter that wraps around the sockets output stream. */
    public PrintWriter serverOut = null;
    public int sockedID = 0;
    public Socket socket = null;
    private Thread listenerThread = null;
    public Vector<String> receivedMessages = null;

    ServerSockets(Socket incoming, int sockedID) {
        try {
            this.sockedID = sockedID;
            this.socket = incoming;
            this.serverOut = new PrintWriter(socket.getOutputStream(), true);
            this.serverIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.receivedMessages = new Vector<String>();
            runListenerThread();

        } catch (Exception e) {
            System.out.println("[ServerSockets] Error ServerSockets(): " + e.getMessage());
        }
    }

    public void runListenerThread() {
        listenerThread = new Thread(new Runnable() {
            @Override
            public void run() {
                String message;
                try {
                    while (!Thread.currentThread().isInterrupted()) {
                        /* Receiving a message from the client */
                        message = serverIn.readLine();
                        /* Check if a message is there */
                        if (message != null) {
                            /* Check if a message is a special command */
                            if (message.equals("receive")) {
                                receiveCommand();
                            } else if (message.equals("erase")) {
                                eraseCommand();
                            } else {
                                /* No command entered */
                                System.out.println("[Server] from Client[" + sockedID + "]: '" + message + "'");
                                receivedMessages.add(message);
                            } /* endif */
                        } /* endif (message != null) */
                    } /* end While */
                } catch (Exception e) {
                    System.out.println("[ServerSocket][Thread] shutdown");
                } finally {
                    close();
                }
            } /* run() */
        }); /* Thread() */
        listenerThread.start();
    } /* runListener() */

    /**
     * Interrupt thread and close socket
     */
    void close() {
        try {
            if (this.listenerThread != null)
                this.listenerThread.interrupt();
            if (this.socket != null)
                this.socket.close();
        } catch (Exception e) {
            System.out.println("[ServerSocket] Error close(): " + e.getMessage());
        }
    } /* close() */

    /**
     * "receive": the server replies by returning all stored messages sent to it
     */
    void receiveCommand() {
        if (receivedMessages == null || receivedMessages.size() == 0) {
            serverOut.println("No messages stored to send.");
        }
        for (String string : receivedMessages) {
            serverOut.println(string);
        }
        System.out.println("[Server][receive] on [Client][" + sockedID
                + "] Finished.");
    } /* receiveCommand() */

    /**
     * "erase": delete all messages on the server side that were sent by that client
     */
    void eraseCommand() {
        if (receivedMessages == null) {
            serverOut.println("Noting to erase.");
        }
        System.out.println(
                "[Server][erase] delete all messages from Client[" + sockedID + "]");
        receivedMessages.clear();
    } /* eraseCommand() */
}
