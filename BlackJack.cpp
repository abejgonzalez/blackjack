#include "Deck.h"
#include "Card.h"
#include "Playingfield.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib");

enum State{
	opening,
	game_type_choice,
	ai_turn,
	player_turn,

	game_start_dealer,
	game_start_person,
	game_hit_question,
	game_player_loss,
	game_dealer_loss,
	game_hit_dealer,
	game_compare_scores,

	game_server_setup,
	game_client_setup,
};

State currentState;
int game_type;
PlayingField* field;

void init();
void blankScreen();
void winsockInit();

int main(void){
	init();

	while (1){
		switch (currentState){
		case opening:{
			std::cout << "Welcome to BlackJack" << std::endl;
			/*Opening animation*/

			currentState = game_type_choice;
		}
			break;

		case game_type_choice:{
			blankScreen();
			std::cout << "Would you like to play against the dealer or another person" << std::endl;
			std::cout << "Play against dealer - Click 1" << std::endl;
			std::cout << "Play against another person - Click 2" << std::endl;
			std::cout << "Choice: ";
			std::cin >> game_type;

			if (game_type != 1 && game_type != 2){
				std::cout << "Incorrect choice please try again" << std::endl;
				currentState = game_type_choice;
			}
			else if (game_type == 1){
				currentState = game_start_dealer;

				std::cout << "You have chosen to play against the dealer. Good Luck!" << std::endl;
			}
			else {
				currentState = game_start_person;

				std::cout << "You have chosen to play against another player. Good luck!" << std::endl;
			}

			field = new PlayingField(new Deck);
		}
			break;

		case game_start_dealer:{

			field->drawDealerCard();
			field->drawDealerCard();
			field->drawPlayerCard();
			field->drawPlayerCard();

			blankScreen();
			std::cout << "The field is set. Both the dealer and the player have both drawn two cards." << std::endl;
			std::cout << "Dealers Cards:" << std::endl;

			for (int i = 0; i < field->dealer_Cards.size(); i++){
				field->dealer_Cards[i].printCardType();
			}

			std::cout << "Players Cards:" << std::endl;

			for (int i = 0; i < field->player_Cards.size(); i++){
				field->player_Cards[i].printCardType();
			}

			currentState = game_hit_question;
		}
			break;
			
		case game_hit_question:{
			char response = '/0';
			std::cout << "Would you like to hit?" << std::endl;
			std::cout << "Yes : y or No : n -------- ";
			std::cin >> response;

			if (response != 'y' && response != 'n'){
				std::cout << "Error in response please try again." << std::endl;
				currentState = game_hit_question;
			}
			else if (response == 'y'){
				std::cout << "You drew a card." << std::endl;
				field->drawPlayerCard();

				std::cout << "Dealers Cards:" << std::endl;

				for (int i = 0; i < field->dealer_Cards.size(); i++){
					field->dealer_Cards[i].printCardType();
				}

				std::cout << "Players Cards:" << std::endl;

				for (int i = 0; i < field->player_Cards.size(); i++){
					field->player_Cards[i].printCardType();
				}

				/*Check if game is over*/
				if (!field->checkPlayerValid()){
					currentState = game_player_loss;
				}
				else{
					currentState = game_hit_question;
				}
			}
			else {
				std::cout << "You chose to stay with your current hand" << std::endl;
				currentState = game_hit_dealer;
			}
		}
			break;

		case game_hit_dealer:{
			blankScreen();
			while (field->checkDealerTotal() < 15){
				std::cout << "The dealer total is less than 15. It draws a card" << std::endl;
				field->drawDealerCard();
				std::cout << "The dealer drew a ";
				field->dealer_Cards.back().printCardType();
			}

			std::cout << "Dealers Cards:" << std::endl;

			for (int i = 0; i < field->dealer_Cards.size(); i++){
				field->dealer_Cards[i].printCardType();
			}

			if (!field->checkDealerValid()){
				currentState = game_dealer_loss;
			}
			else{
				currentState = game_compare_scores;
			}
		}
			break;

		case game_dealer_loss:{
			blankScreen();
			std::cout << "The dealer lost with a score of " << field->checkDealerTotal() << ". Player won with score of " << field->checkPlayerTotal() << "." << std::endl;
			std::cout << "Final Playing Field: " << std::endl;

			std::cout << "Dealers Cards:" << std::endl;

			for (int i = 0; i < field->dealer_Cards.size(); i++){
				field->dealer_Cards[i].printCardType();
			}

			std::cout << "Players Cards:" << std::endl;

			for (int i = 0; i < field->player_Cards.size(); i++){
				field->player_Cards[i].printCardType();
			}

			char response = '/0';
			std::cout << "Would you like to play again?" << std::endl;
			std::cout << "Yes : y or No : n -------- ";
			std::cin >> response;

			if (response != 'y' || response != 'n'){
				std::cout << "Error in response exiting." << std::endl;
			}
			else if (response == 'y'){
				currentState = game_type_choice;
			}
			else{
				std::cout << "Exiting" << std::endl;
			}
		}
			break;
		case game_player_loss:{
			blankScreen();
			std::cout << "The player lost with a score of " << field->checkPlayerTotal() << ". Dealer won with score of " << field->checkDealerTotal() << "." << std::endl;
			std::cout << "Final Playing Field: " << std::endl;

			std::cout << "Dealers Cards:" << std::endl;

			for (int i = 0; i < field->dealer_Cards.size(); i++){
				field->dealer_Cards[i].printCardType();
			}

			std::cout << "Players Cards:" << std::endl;

			for (int i = 0; i < field->player_Cards.size(); i++){
				field->player_Cards[i].printCardType();
			}

			char response = '/0';
			std::cout << "Would you like to play again?" << std::endl;
			std::cout << "Yes : y or No : n -------- ";
			std::cin >> response;

			if (response != 'y' && response != 'n'){
				std::cout << "Error in response exiting." << std::endl;
			}
			else if (response == 'y'){
				currentState = game_type_choice;
			}
			else{
				std::cout << "Exiting" << std::endl;
			}
		}
			break;
		case game_compare_scores:{
			if (field->checkDealerTotal() <= field->checkPlayerTotal()){
				currentState = game_dealer_loss;
			}
			else {
				currentState = game_player_loss;
			}
		}
			break;
		case game_start_person:{
			char choice = '\0';

			std::cout << "Would you like to host or connect to a game.";
			std::cout << "Host-h Connect-c ------ ";
			std::cin >> choice;

			if (choice != 'c' && choice != 'h'){
				std::cout << "Incorrect input. Try again" << std::endl;
				currentState = game_start_person;
			}
			else if(choice == 'c'){
				currentState = game_client_setup;
			}
			else{
				currentState = game_server_setup;
			}
		}
			break;
		case game_client_setup:{
			winsockInit();

			SOCKADDR_IN addr;
			int addrLen = sizeof(addr);
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			addr.sin_port = htons(1111);
			addr.sin_family = AF_INET;

			SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
			if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0){
				MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
				return 0;
			}
			else{
				std::cout << "Connected" << std::endl;
				char recievedMess[256];
				recv(Connection, recievedMess, sizeof(recievedMess), NULL);
				std::cout << "I recieved: " << recievedMess << std::endl;
				system("pause");
			}


		}
			break;
		case game_server_setup:{
			
			winsockInit();
			SOCKADDR_IN addr;
			int addrLen = sizeof(addr);
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//Address
			addr.sin_port = htons(1111); //Port number
			addr.sin_family = AF_INET; //IPv4

			SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket
			bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
			listen(sListen, SOMAXCONN); //Listen for connection

			SOCKET newConnection;
			newConnection = accept(sListen, (SOCKADDR*)&addr, &addrLen);
			if (newConnection == 0){
				std::cout << "Failed to accept the clients connection." << std::endl;
			}
			else{
				std::cout << "Client connected" << std::endl;
				char message[256] = "This is the message to send to the client";
				send(newConnection, message, sizeof(message), NULL);
			}
			system("pause");
			return 0;

		}
			break;
		}
	}
}

void init(){
	game_type = 0;
	currentState = opening;
}

void blankScreen(){
	/*Adds an extra amount of spaces to clear the screen*/
	for (int i = 0; i < 50; i++){
		std::cout << '\n';
	}
}

void winsockInit(){
	/*Winsock Startup*/
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0){
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
}