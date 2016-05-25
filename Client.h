#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib");

class Client
{
public:
	Client(char* ipAddr, int portNum);
	bool connectToServer();
	bool retrieveFromServer(char* location, int lenLocation);
	void sendToServer(char* location, int lenLocation);
	~Client();
private:
	SOCKADDR_IN addr;
	SOCKET client;
};

#endif