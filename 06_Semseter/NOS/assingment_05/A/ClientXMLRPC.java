import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * This is a simple XML-RPC client that demonstrates how to use the execute method
 * of XmlRpcClient to call methods on an XML-RPC server. The client sets up a client
 * and tests the server's 'echo', 'currentTimeSystemMillis', and 'currentTimeGregorianPretty'
 * methods.
 *
 */
public class ClientXMLRPC {

    /**
     * This is the main method for the XML-RPC client.
     * It sets up a client and tests the server's 'echo', 'currentTimeSystemMillis',
     * and 'currentTimeGregorianPretty' methods using the execute method of XmlRpcClient.
     * @param args Command line arguments (not used).
     * @throws XmlRpcException If an error occurs during XML-RPC communication.
     * @throws MalformedURLException If the URL of the server is malformed.
     */
    public static void main(String[] args) throws XmlRpcException, MalformedURLException {
        System.out.println("ClientXMLRPC");
        /* Setup */
        XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
        String clientUrl = "http://127.0.0.1:5000";
        config.setServerURL(new URL(clientUrl));


        XmlRpcClient rpcClient = new XmlRpcClient();
        rpcClient.setConfig(config);

        /* Test setup */
        String resultString;
        Integer resultInteger;
        List params = new ArrayList();
        String method;

        /* Test echo */
        method = "SERVER.echo";
        params.clear();
        params.add("Hello Server");
        resultString = (String) rpcClient.execute(method, params);
        System.out.println(resultString);

        /* Test currentTimeSystemMillis */
        method = "SERVER.currentTimeSystemMillis";
        params.clear();
        resultString = (String) rpcClient.execute(method,params);
        System.out.println("System time: " + resultString);

        /* Test currentTimeGregorianPretty */
        method = "SERVER.currentTimeGregorianPretty";
        params.clear();
        resultString = (String) rpcClient.execute(method,params);
        System.out.println("Gregorian time: " + resultString);

    } /* main(String[] args) */

} /* ClientXMLRPC */
