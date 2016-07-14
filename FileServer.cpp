//============================================================================
// Name        : FileServer.cpp
// Author      : LiMin
// Version     :
// Copyright   : Public Domain
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "lmFileServer.h"



using namespace std;

int main() {
	cout << "This is the test program for FileServer" << endl;

	// Create a Server
	lm_File_Server FileServer_Test(1116);

	// wait for connection requests and handle requests
	while(true)
	{
		FileServer_Test.RecvFile("test.png");
	}
	return 0;
}
