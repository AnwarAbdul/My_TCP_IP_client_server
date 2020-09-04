/*
 * @file client.cpp
 * @brief Main source file for the TCP/IP client program
 *
 * @author Anwar Abdul Jabbar
 * @date September 4, 2020
 */

#include "helper.h"
#include "errors.h"

int main(){
	
	int ret;
	//Creating a socket
	int _socket = create_socket();
	if(_socket == -1){
#if DEBUG
		std::cout<<"Error creating client socket\n";
#endif
		return ERR_CREATE_SOCKET;
	}

	//Setting up the socket with address which shall be "localhost" and the port number to which it must connect to
	sockaddr_in socket_address = setup_socket(54000,"127.0.0.1");

	//Connect to the server
	ret = connect(_socket,(sockaddr *)&socket_address,sizeof(socket_address));
	if(ret == -1){
#if DEBUG
		std::cout<<"Could not connect client to server\n";
#endif
		return ERR_CONNECTING_CLIENT_TO_SERVER;
	}

	//Send data to server
	char buf[4096];
	std::string input_text;
	while(true){
		memset(buf,0,4096);
		std::cout<<">";
		std::getline(std::cin,input_text);
		strcpy(buf,input_text.c_str());
		ret = send(_socket,buf,input_text.length(),0);
		if(ret == -1){
			std::cout<<"Could not send to server\n";
			continue;
		}

		int bytes_received = recv(_socket,buf,4096,0);
		if(bytes_received == 0 || bytes_received == -1){
			std::cout<<"Connection lost\n";
			close(_socket);
			return ERR_CONNECTION_LOST;
		}
		std::cout<<"SERVER>"<<std::string(buf,0,bytes_received)<<"\n";
	}
	
	//Close socket
	close(_socket);
	return 0;
}
