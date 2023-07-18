# General comments

Your code style is a mirror of your mind! Use comments where necessary, take
care for clean indentation. If your program does not compile then it receives
zero points.

Try to use the concepts and mechanisms we learned in the lecture when
appropriate. For instance, use javadoc comments, proper visibility for fields,
package definitions, and so on without being explicitly mentioned in the
assignments.

# Message Relay System: Description and preparation

Goal of this exercise is to create a system consisting of a server and clients
where the clients can send text messages to the server via sockets. The server 
then stores these messages and, when prompted, relays all stored messages to
the requesting client. Create a `Message` class that contains at least the
following fields:
* the text of message
* the ID of the client which has sent the message

If the client sends any text to the server, it is interpreted as a text message
to be stored as a Message object on the server. However, there are two special
commands available. If the sent message consists only of one of the following,
it is not stored, but interpreted by the server as follows:

* "receive": the server replies by returning all stored messages sent to it 
             (except those sent by that client)
* "erase":   delete all messages on the server side that were sent by that
             client

# Assignment A - Client

Implement the client.

* On startup, it should automatically connect to the server.
* After the connection it should receive its ID assigned and sent by the server.
* Subsequently it reads user input from the command line and sends it to the server.
* If "receive" is entered and sent to the server, it receives messages from the server
  and displays them in the terminal.
* If "exit" is entered, the client terminates.

Note that technically it is not necessary to implement a concurrent client for
this assignment. (However, you may, if you wish.)

You can test the client by using netcat (https://nmap.org/ncat/). You can start a
server with the command

    nc -l -p [PORT]

See also https://ubidots.com/blog/how-to-simulate-a-tcpudp-client-using-netcat/

# Assignment B - Server

Implement the server.

* It should be able to serve multiple clients concurrently. Choose an
  appropriate method to do this. You can either use (a) non-blocking I/O or (b)
  blocking I/O.
* When a client connects, the server assigns it an ID and sends it to the
  client.
* After that, it should read all messages sent from the clients and store each
  of them as a `Message` object in one (1) collection.
* If the server receives a message containing only the string "receive" then it
  sends back all stored messages from the other clients.
* If the server receives a message containing only the string "erase" then it
  removes all stored messages that have been sent by that client.