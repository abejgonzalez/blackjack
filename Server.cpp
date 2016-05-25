#include "Server.h"


Server::Server(char* ipAddr, int portNum){
	addr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	addr.sin_port = htons(portNum);
	addr.sin_family = AF_INET;

	mainServer = socket(AF_INET, SOCK_STREAM, NULL);

	bind(mainServer, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
}

void Server::listenForClient(){
	listen(mainServer, SOMAXCONN); //Listen for connection
}

bool Server::acceptClient(){
	int addrLen = sizeof(addr);
	connectServer = accept(mainServer, (SOCKADDR*)&addr, &addrLen);
	if (connectServer == 0){
		return false;
	}
	else{
		return true;
	}
}

void Server::sendToClient(char* location, int lenLocation){
	send(connectServer, location, lenLocation, NULL);
}

Server::~Server()
{
}
