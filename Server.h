#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib");

class Server
{
public:
	Server(char* ipAddr, int portNum);
	void listenForClient();
	bool acceptClient();
	void sendToClient(char* location, int lenLocation);
	bool retrieveFromClient(char* location, int lenLocation);
	~Server();
private:
	SOCKADDR_IN addr;
	SOCKET mainServer;
	SOCKET connectServer;
};

#endif