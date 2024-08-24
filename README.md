# Reactor And-Thread-Per-Client Server
The project is a book club. Users can sign up for reading clubs and borrow books from each other. 
a server, which provides STOMP (Simple-Text-OrientedMessaging-Protocol) server services, and a client, which a user can use to interact with the rest of the users. 
The server was implemented in Java and supported both Thread-Per-Client (TPS) and the Reactor methodologies, choosing which one according to arguments given on startup. 
The client is implemented in C++ and holds the required logic. All communication between the clients and the server follows the STOMP protocol.

# Thread per client server vs Reactor server
Multiple clients can be connected to the server, interact with it, and interact with each other. 
As the server's side is activated, we decide what pattern to use, a thread per client-server or reactor server.
Thread-per-client generates a thread for every client connecting to the server and does all the relevant jobs, such as: confirming the connection, reading the request (the message from the client), doing the relevant service, etc.. and once the client's connection is terminated, the thread has done its job and can be terminated too. 
The Reactor server initiates a fixed-size pool of threads and assigns a thread for every kind of work created by incoming client data. for example, one thread is responsible for converting a stream of characters to bytes. After finishing its assignment, the thread goes back to the "threads pool" and waits for the next assignment of the same kind he is responsible for.
