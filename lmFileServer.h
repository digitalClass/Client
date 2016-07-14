/*
 * lmFileServer.h
 *
 *  Created on: 2016年7月12日
 *      Author: limin
 */

#ifndef LMFILESERVER_H_
#define LMFILESERVER_H_


#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>
#include <iostream>

#include <fstream> // file stream operation
#include <iomanip> // Custom the output and input
#include <iostream>

using namespace std;


class lm_File_Server {
	// Constructor and Destructor
public:
	lm_File_Server();
	lm_File_Server(int port);
	virtual ~lm_File_Server();
	// Attributions
	//int serverip;
	int serverport;
	int server_fd; // the socket fd of the server

	// Functions
private:
	int ServerInit(int port);
public:
	int RecvFile(char* filename);
};

#endif /* LMFILESERVER_H_ */
