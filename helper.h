/*
 *
 * @file helper.h
 * @brief Header file containing the APIs used in the main file
 *
 * @author Anwar Abdul Jabbar
 * @date September 4, 2020
 */

#ifndef __HELPER_H__
#define __HELPER_H__

#define DEBUG 1

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <fstream>

/*
 * @brief API for creating a socket
 *
 * @param None
 * @return Integer type return code of execution of "socket" call
 */
int create_socket();

/*
 * @brief API for setting up socket with an address and port
 *
 * @param Port number to be used for socket of integer type
 * @param Address of socket to be used in string format
 * @return sockaddr_in type structure is returned which will have the address inside sin_addr member and port info in sin_port 
 */
sockaddr_in setup_socket(int,std::string);

/*
 * @brief API for binding socket ID to specified address and port info present in its corresponding sockaddr_in structure
 *
 * @param Socket file id
 * @param sockaddr_in pointer to the socket info of address & port
 * @return Return code of "bind" system call
 */
int bind_socket_port(int,sockaddr_in *);

/*
 * @brief API for starting the listening on listening socket
 *
 * @param Listening socket file ID
 * @return Integer return code of the "listen" system call
 */
int listening(int);

/*
 * @brief API for listening socket to accept client socket connection
 *
 * @param Listening socket file ID
 * @param sockaddr_in structure pointer of client socket to store client socket information within sin_addr and sin_port members
 * @param socklen_t pointer to client socket address information
 * @return Integer return code of "accept" system call used which will actually be a file ID for client socket
 */
int accept_connections(int,sockaddr_in *,socklen_t *);

#endif 
