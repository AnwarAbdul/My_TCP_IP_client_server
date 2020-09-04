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
	int listening_socket = socket(PF_INET,SOCK_STREAM,0); //SOCK_STREAM provides reliable 2 way communication based byte streams.	
	if(listening_socket == -1){
#if DEBUG
		std::cout<<"Error creating listening socket\n";
#endif
		return ERR_CREATE_SOCKET;
	}

	sockaddr_in listening_socket_address;
	listening_socket_address.sin_family = PF_INET;
	listening_socket_address.sin_port = htons(54000);

	int ret = inet_pton(PF_INET,"127.0.0.1",(void *)&listening_socket_address.sin_addr);
	if(ret == 0 || ret == -1){
#if DEBUG
		std::cout<<"Return code = "<<ret<<"\n";
		std::cout<<"System error. Could not translate the specified address to sockaddr_in.sin_addr family\n";
#endif
		return ERR_INET_PTON_LISTENING_SOCKET;
	}

	if(bind(listening_socket,(sockaddr *)&listening_socket_address,sizeof(listening_socket_address)) == -1){
#if DEBUG
		std::cout<<"Could not bind the listening socket to port\n";
#endif
		return ERR_BIND_SOCKET;
	}

	if(listen(listening_socket,SOMAXCONN) == -1){
#if DEBUG
		std::cout<<"Error listening on listening socket\n";
#endif
		return ERR_LISTENING;
	}

	sockaddr_in client_socket_address;
	socklen_t client_socket_size = sizeof(client_socket_address);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	int client_socket = accept(listening_socket,(sockaddr *)&client_socket_address,&client_socket_size);
	if(client_socket == -1){
#if DEBUG
		std::cout<<"Error connecting client\n";
#endif
		return ERR_CLIENT_CONNECT;
	}
	
	close(listening_socket);
	
	memset(host,0,NI_MAXHOST);
	memset(service,0,NI_MAXSERV);
	
	ret = getnameinfo((sockaddr *)&client_socket_address,sizeof(client_socket_address),host,NI_MAXHOST,service,NI_MAXSERV,0);
	if(ret)
		std::cout<<host<<" connected on "<<service<<"\n";
	else{
		inet_ntop(PF_INET,&client_socket_address.sin_addr,host,NI_MAXHOST);
		std::cout<<host<<" connected on "<<ntohs(client_socket_address.sin_port)<<"\n";
	}

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
