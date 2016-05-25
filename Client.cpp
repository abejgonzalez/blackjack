#include "Client.h"


Client::Client(char* ipAddr, int portNum){
	int addrLen = sizeof(addr);
	addr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	addr.sin_port = htons(portNum);
	addr.sin_family = AF_INET;

	client = socket(AF_INET, SOCK_STREAM, NULL);
}

bool Client::connectToServer(){
	if (connect(client, (SOCKADDR*)&addr, sizeof(addr)) != 0){
		return false;
	}
	else{
		return true;
	}
}


bool Client::retrieveFromServer(char* location, int lenLocation){
	if (recv(client, location, lenLocation, NULL) != 0){
		return false;
	}
	else{
		return true;
	}
}

Client::~Client(){

}
