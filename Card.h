#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<string>

class Card {
	public:
		/*Data*/
		enum Color
		{
			Red,
			Black,
		};
		enum Suit
		{
			Spade,
			Heart,
			Club,
			Diamond
		};

		/*Functions*/
		Card(int number, Suit suit, Color color);
		void printCardType();
		int getNumber();

	private:
		int m_number;
		Suit m_sType;
		Color m_cType;

	protected:
};

#endif