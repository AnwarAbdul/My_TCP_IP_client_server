/*
 * @file helper.cpp
 * @brief Helper APIs used in the program are defined here
 *
 * @author Anwar Abdul Jabbar
 * @date September 4, 2020
 */

#include "helper.h"

int create_socket(){
	return socket(PF_INET,SOCK_STREAM,0); //SOCK_STREAM is meant for 2 way communication byte streams
}

sockaddr_in setup_listening_socket(int listening_socket, int portNumber){
	sockaddr_in address;

	address.sin_family = PF_INET;
	address.sin_port = htons(portNumber); //htons helps to convert the given port number into a format which will be understood at the right endian level 
	inet_pton(PF_INET,"127.0.0.1",(void *)&address.sin_addr);

	return address;
}

int bind_socket_port(int listening_socket, sockaddr_in* address){
	return bind(listening_socket,(sockaddr *)address,sizeof(*address));
}

int listening(int listening_socket){
	return listen(listening_socket,SOMAXCONN);
}

int accept_connections(int listening_socket, sockaddr_in *client_socket_address, socklen_t *client_socket_size){
	int client_socket = accept(listening_socket,(sockaddr *)client_socket_address,client_socket_size);
	return client_socket;
}
