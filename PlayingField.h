#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include "Deck.h"
#include <vector>
#include <iostream>

class PlayingField{
	public:
		PlayingField(Deck* deck);
		~PlayingField();
		std::vector<Card> dealer_Cards;
		std::vector<Card> player_Cards;
		void drawDealerCard();
		void drawPlayerCard();
		void clearField();
		void printField();
		bool checkPlayerValid();
		bool checkDealerValid();
		int checkDealerTotal();
		int checkPlayerTotal();
	private:
		Deck* m_Deck;
	protected:
};

#endif