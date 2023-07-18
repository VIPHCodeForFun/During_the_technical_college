import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.server.PropertyHandlerMapping;
import org.apache.xmlrpc.webserver.WebServer;

import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;

/**
 * The TimeServerXMLRPC class provides a simple implementation of an XML-RPC server
 * that exposes three methods: currentTimeSystemMillis(), currentTimeGregorianPretty(),
 * and echo(String string).
 * The class also provides a main method to start the server.
 * The server listens on port 5000 and can be accessed by an XML-RPC client.
 * The methods of this class are invoked by an XML-RPC client by calling the methods on
 * the server object with the name "SERVER".
 */
public class TimeServerXMLRPC {

    /**
     * Returns the current system time in seconds as a string.
     * @return a string representation of the current system time in seconds
     */
    public String currentTimeSystemMillis(){
        System.out.println("Client calling: 'currentTimeSystemMillis()'");
        long currentTimeInSeconds = System.currentTimeMillis() / 1000L;
        String timeInSecondsString = Long.valueOf(currentTimeInSeconds).toString();
        return timeInSecondsString;
    } /* currentTimeSystemMillis */

    /**
     *
     * Returns the current time in the Gregorian calendar format as a pretty string.
     * The format used is "M/d/yy h:mm a z".
     * @return A string representation of the current time in the Gregorian calendar format.
     */
    public String currentTimeGregorianPretty() {
        try {
            System.out.println("Client calling: 'currentTimeGregorianPretty()'");
            DateFormat df = new SimpleDateFormat("M/d/yy h:mm a z");
            df.setLenient(false);
            return df.parse("6/29/2012 5:15 PM IST").toString();
        }catch (ParseException pe) {
            return pe.toString();
        }
    } /* currentTimeGregorianPretty */

    /**
     * Returns a string that is an echo of the input string.
     * @param string the input string to be echoed
     * @return a string that is an echo of the input string
     */
    public String echo(String string){
        System.out.println("Client calling: 'echo(String string)'");
        return "Server echo :'" + string + "'";
    }

    /**
     * This is the main method for the XML-RPC server.
     * A simple XML-RPC server that exposes the methods of the TimeServerXMLRPC class
     * and listens on port 5000.
     */
    public static void main(String[] args) throws IOException, XmlRpcException {
        int port = 5000;
        System.out.println("TimeServerXMLRPC");
        WebServer webServer = new WebServer(port);

        PropertyHandlerMapping mapping = new PropertyHandlerMapping();
        mapping.addHandler("SERVER", TimeServerXMLRPC.class);

        webServer.getXmlRpcServer().setHandlerMapping(mapping);
        webServer.start();
    } /* main(String[] args) */

} /* TimeServerXMLRPC */
