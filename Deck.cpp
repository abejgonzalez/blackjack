#include "Deck.h"
#include <stdlib.h>
#include <ctime>


Deck::Deck()
{
	srand(time(NULL));

	m_Deck.clear();
	/*Add 52 cards to the deck*/
	for (int i = 0; i <= 13; i++){
		for (int j = 0; j < 4; j++){
			if (j == 1 || j == 3){
				m_Deck.push_back(Card(i, (Card::Suit)j, Card::Red));
			}
			else{
				m_Deck.push_back(Card(i, (Card::Suit)j, Card::Black));
			}
		}
	}
}

void Deck::printDeck(){
	for (int i = 0; i < m_Deck.size(); i++){
		m_Deck[i].printCardType();
	}
}

Card Deck::drawCard(){
	int myRandNumber = rand() % 52;

	Card temp = m_Deck[myRandNumber];

	m_Deck.erase(m_Deck.begin() + myRandNumber);
	return temp;
}

void Deck::replaceCard(Card card){
	m_Deck.push_back(card);
}