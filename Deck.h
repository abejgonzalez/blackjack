#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck{
	public:
		void printDeck();
		Card drawCard();
		void replaceCard(Card card);
		Deck();
	private:
		std::vector<Card> m_Deck;
		std::vector<int> m_Used;
	protected:

};

#endif