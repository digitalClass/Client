/*
 * lmFileServer.cpp
 *
 *  Created on: 2016年7月12日
 *      Author: limin
 */

#include "lmFileServer.h"

lm_File_Server::lm_File_Server() {
	serverport = 1116;
	server_fd  = ServerInit(serverport);
}
lm_File_Server::lm_File_Server(int port)
{
	serverport = port;
	server_fd = ServerInit(serverport);
}

lm_File_Server::~lm_File_Server() {
	// TODO Auto-generated destructor stub
}

int lm_File_Server::ServerInit(int port)
{
	// The Server address
	struct sockaddr_in server_addr;
	int socket_fd;
	// Create the server socket
	if((socket_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket Create Error:");
		exit(-1);
	}

	// Set the server end-point attributes
	bzero(&server_addr, sizeof(struct sockaddr) );
	server_addr.sin_family = AF_INET; // IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// server_addr.sin_addr.s_addr = inet_addr("192.168.1.103");
	server_addr.sin_port = htons(port);

	// Set the Address reuse
	int reuse = 1;
	if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		perror("SetSocketOpet Error:");
		exit(-1);
	}

	// bind the server socket
	if(bind(socket_fd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1)
	{
		perror("Bind Error:");
		exit(-1);
	}

	// set the max client num
	if(listen(socket_fd, 10) == -1)
	{
		perror("Listen Initialization Error:");
		exit(-1);
	}

	//
	return socket_fd;
}

int lm_File_Server::RecvFile(char* filename)
{
	unsigned int sin_size = sizeof(struct sockaddr_in);
	int newClient_fd;
	sockaddr_in newClient_addr;

	// Blocking the server and wait for new connection
	newClient_fd = accept(server_fd, (struct sockaddr*)(&newClient_addr), &sin_size);
	if(newClient_fd == -1)
	{
		perror("Accept Error:");
		exit(-1);
	}

	// Print the New Client Information
	cout << "New Client Connected:" << inet_ntoa(newClient_addr.sin_addr) << endl;
	// Receive the data from the new client
	char buffer[4096] = {0};
	unsigned int nbytes = 0;
	FILE *fp = fopen(filename, "w");
	if(fp == NULL)
	{
		perror("Failed to open file for writing!");
		exit(-1);
	}
	// flush the buffer
	bzero(buffer, 4096);
	while((nbytes = recv(newClient_fd, buffer, 4096, 0)) > 0)
	{
		/*
		 * The client should close the connection immediately after sent file,
		 * to Ensure this loop break.
		 * */
		// Write the buffer to the file
		if(fwrite(buffer, sizeof(char), nbytes, fp) < nbytes)
		{
			perror("Write file error!");
			break;
		}
		bzero(buffer, 4096);
	}
	cout << "File Received!" << endl;
	char* data = "Done!";
	if((write(newClient_fd, data, strlen(data))) == -1)
	{
		perror("Write Error:");
		return -1;
	}
	// close the current connection
	close(newClient_fd);
	cout << "Connection Closed!" << endl;
}
