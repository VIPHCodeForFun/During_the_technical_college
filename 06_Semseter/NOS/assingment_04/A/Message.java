package A;

public class Message {
    private String message;
    private int clientID;

    /* Constructors */
    Message(int clientID, String message) {
        this.message = message;
        this.clientID = clientID;
    }

    /* Getter */
    public String getMessage() {
        return message;
    }

    public int getClientID() {
        return clientID;
    }

    /* Setter */
    public void setMessage(String message) {
        this.message = message;
    }

    public void setClientID(int clientID) {
        this.clientID = clientID;
    }

}
