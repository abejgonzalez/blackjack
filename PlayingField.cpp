#include "PlayingField.h"


PlayingField::PlayingField(Deck* deck)
{
	m_Deck = deck;
}


PlayingField::~PlayingField()
{
	clearField();
	delete m_Deck;
}

void PlayingField::drawDealerCard(){
	dealer_Cards.push_back(m_Deck->drawCard());
}

void PlayingField::drawPlayerCard(){
	player_Cards.push_back(m_Deck->drawCard());
}

void PlayingField::clearField(){
	for (int i = 0; i < dealer_Cards.size(); i++){
		m_Deck->replaceCard(dealer_Cards.back());
		dealer_Cards.pop_back();
	}
	for (int i = 0; i < player_Cards.size(); i++){
		m_Deck->replaceCard(player_Cards.back());
		player_Cards.pop_back();
	}
}

bool PlayingField::checkPlayerValid(){
	int runningTotal = 0;
	int amountOfAces = 0;
	for (int i = 0; i < player_Cards.size(); i++){
		if (player_Cards[i].getNumber() >= 1 && player_Cards[i].getNumber() <= 10){
			runningTotal += player_Cards[i].getNumber();
		}
		else if (player_Cards[i].getNumber() > 10 && player_Cards[i].getNumber() <= 13){
			runningTotal += 10;
		}
		else{
			amountOfAces += 1;
		}
	}

	if (runningTotal > 21){
		return false;
	}

	for (int i = 0; i < amountOfAces; i++){
		if (runningTotal + 1 == 21){
			runningTotal += 1;
		}
		else if (runningTotal + 11 == 21){
			runningTotal += 11;
		}
		else if (runningTotal + 11 < 21){
			runningTotal += 11;
		}
		else{
			runningTotal += 1;
		}
	}

	if (runningTotal > 21){
		return false;
	}

	return true;
}

bool PlayingField::checkDealerValid(){
	int runningTotal = 0;
	int amountOfAces = 0;

	for (int i = 0; i < dealer_Cards.size(); i++){
		if (dealer_Cards[i].getNumber() >= 1 && dealer_Cards[i].getNumber() <= 10){
			runningTotal += dealer_Cards[i].getNumber();
		}
		else if (dealer_Cards[i].getNumber() > 10 && dealer_Cards[i].getNumber() <= 13){
			runningTotal += 10;
		}
		else{
			amountOfAces += 1;
		}
	}

	if (runningTotal > 21){
		return false;
	}

	for (int i = 0; i < amountOfAces; i++){
		if (runningTotal + 1 == 21){
			runningTotal += 1;
		}
		else if (runningTotal + 11 == 21){
			runningTotal += 11;
		}
		else if (runningTotal + 11 < 21){
			runningTotal += 11;
		}
		else{
			runningTotal += 1;
		}
	}

	if (runningTotal > 21){
		return false;
	}

	return true;
}

int PlayingField::checkDealerTotal(){
	int runningTotal = 0;
	int amountOfAces = 0;

	for (int i = 0; i < dealer_Cards.size(); i++){
		if (dealer_Cards[i].getNumber() >= 1 && dealer_Cards[i].getNumber() <= 10){
			runningTotal += dealer_Cards[i].getNumber();
		}
		else if (dealer_Cards[i].getNumber() > 10 && dealer_Cards[i].getNumber() <= 13){
			runningTotal += 10;
		}
		else{
			amountOfAces += 1;
		}
	}

	for (int i = 0; i < amountOfAces; i++){
		if (runningTotal + 1 == 21){
			runningTotal += 1;
		}
		else if (runningTotal + 11 == 21){
			runningTotal += 11;
		}
		else if (runningTotal + 11 < 21){
			runningTotal += 11;
		}
		else{
			runningTotal += 1;
		}
	}

	return runningTotal;
}

int PlayingField::checkPlayerTotal(){
	int runningTotal = 0;
	int amountOfAces = 0;
	for (int i = 0; i < player_Cards.size(); i++){
		if (player_Cards[i].getNumber() >= 1 && player_Cards[i].getNumber() <= 10){
			runningTotal += player_Cards[i].getNumber();
		}
		else if (player_Cards[i].getNumber() > 10 && player_Cards[i].getNumber() <= 13){
			runningTotal += 10;
		}
		else{
			amountOfAces += 1;
		}
	}

	for (int i = 0; i < amountOfAces; i++){
		if (runningTotal + 1 == 21){
			runningTotal += 1;
		}
		else if (runningTotal + 11 == 21){
			runningTotal += 11;
		}
		else if (runningTotal + 11 < 21){
			runningTotal += 11;
		}
		else{
			runningTotal += 1;
		}
	}

	return runningTotal;
}

void PlayingField::printField(){
	std::cout << "Dealers Cards:" << std::endl;
	for (int i = 0; i < field->dealer_Cards.size(); i++){
		field->dealer_Cards[i].printCardType();
	}

	std::cout << "Players Cards:" << std::endl;
	for (int i = 0; i < field->player_Cards.size(); i++){
		field->player_Cards[i].printCardType();
	}
}