/*
 * @file server.cpp
 * @brief main file for the TCP/IP server. 
 *
 * @author Anwar Abdul Jabbar
 * @date September 4, 2020
 *
 */

#include "helper.h"
#include "errors.h"

int main(){

	int ret;
	//Creating a listening socket
	int listening_socket = create_socket(); 	
	if(listening_socket == -1){
#if DEBUG
		std::cout<<"Error creating listening socket\n";
#endif
		return ERR_CREATE_SOCKET;
	}

	//Setting up the listening socket address and port
	sockaddr_in listening_socket_address = setup_socket(54000,"0.0.0.0");

	//Binding the listening socket to the address and port specified
	ret = bind_socket_port(listening_socket,&listening_socket_address);
	if(ret == -1){
#if DEBUG
		std::cout<<"Could not bind the listening socket to port\n";
#endif
		return ERR_BIND_SOCKET;
	}

	//Intiating listening on the listening socket
	ret = listening(listening_socket);
	if(ret == -1){
#if DEBUG
		std::cout<<"Error listening on listening socket\n";
#endif
		return ERR_LISTENING;
	}

	//Setting up client socket
	sockaddr_in client_socket_address;
	socklen_t client_socket_size = sizeof(client_socket_address);
	//Char arrays for storing host or client information
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	//Accept connections from client sockets on listening socket
	int client_socket = accept_connections(listening_socket,&client_socket_address,&client_socket_size);
	if(client_socket == -1){
#if DEBUG
		std::cout<<"Error connecting client\n";
#endif
		return ERR_CLIENT_CONNECT;
	}

	//Closing listening socket	
	close(listening_socket);
	
	//Retrieving host/client info
	memset(host,0,NI_MAXHOST);
	memset(service,0,NI_MAXSERV);
	ret = getnameinfo((sockaddr *)&client_socket_address,sizeof(client_socket_address),host,NI_MAXHOST,service,NI_MAXSERV,0);
	if(ret)
		std::cout<<host<<" connected on "<<service<<"\n";
	else{
		inet_ntop(PF_INET,&client_socket_address.sin_addr,host,NI_MAXHOST);
		std::cout<<host<<" connected on "<<ntohs(client_socket_address.sin_port)<<"\n";
	}

	//Sending and receving data from client
	char buf[4096];
	while(true){
		memset(buf,0,4096);
		int bytes_received = recv(client_socket,buf,4096,0);
		if(bytes_received == -1 || bytes_received == 0){
			std::cout<<"Connection lost\n";
			close(client_socket);
			return ERR_CONNECTION_LOST;
		}
	
		std::cout<<"Received: "<<std::string(buf,0,bytes_received)<<"\n";

		send(client_socket,buf,4096,0);		
	}
	close(client_socket);
	return 0;	
}
