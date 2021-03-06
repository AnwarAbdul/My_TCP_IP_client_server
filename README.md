This is a simple TCP/IP client server project written in C++ for Unix based operating systems. Tested on MacOS & Linux.

Usage
1. Compilation needs a Unix OS with g++ compiler
2. There exists a Makefile in the folder which will implement the compilation rules
3. Run $make build
4. 2 executables, "tcpip_server" & "tcpip_client" are created.
5. Server can be run on a system by executing $./tcpip_server
6. The client can be run on same system or different one by executing $./tcp_client
7. The server needs to be configured with its port number and IP address in "server_config.txt" file in subsequent lines. By default the server address provided is "127.0.0.1" which is localhost and port number as 54000
8. The client initiates the communication as of now

Steps followed for Server creation
1. Create listening socket using "socket" system call
2. Intialize a sockaddr_in structure which will have the listening socket details such as port number, sin_family and the actual IP address in Networking format
3. Bind the socket created to the particular port number and address
4. Setup the socket for listening using "listen" system call
5. Initialize a client socket and also a structure of type sockaddr_in which will have the client socket address meaning the address details of the client which will be trying for connecting to listening socket
6. Setup the system call "accept" for accepting connections from a client socket to the listening socket
7. Close the listening socket. This ensures that there will be only 1 client socket communication.
8. The while loop for receiving messages from client and processing it comes after the "close" call. This is because there are queues internally which will be processing connections and messages till the connection is closed from client side based on the setup for client and listening socket done earlier. And as specified earlier, the listening socket will close after 1 client is connected to it, meaning it will not allow further client connections.
9. Inside while loop, "recv" call processes the message from client and the same is relayed back to client using "send".

Steps followed for creating TCP/IP client
1. Create a socket using "socket" system call
2. Initialize a sockaddr_in structure for the socket with the target server's port number and IP address. If you are trying to connect to server on your localhost, provide "127.0.0.1" string
3. Use "connect" system call to connect to server with created socket
4. Once connected, send messages from stdin.
