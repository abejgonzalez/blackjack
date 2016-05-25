#include "Card.h"

Card::Card(int number, Suit suit, Color color){
	m_number = number;
	m_sType = suit;
	m_cType = color;
}

void Card::printCardType(){
	/*List the color*/
	if (m_cType == Red){
		std::cout << "Red ";
	}
	else {
		std::cout << "Black ";
	}

	/*List the number*/
	if (m_number == 0){
		std::cout << "Ace ";
	}
	else if (m_number > 0 && m_number <= 10){
		std::cout << m_number << ' ';
	}
	else{
		if (m_number == 11){
			std::cout << "Jack ";
		}
		else if (m_number == 12){
			std::cout << "Queen ";
		}
		else if (m_number == 13){
			std::cout << "King ";
		}
	}

	/*List the Type*/
	switch (m_sType){
	case Spade:
		std::cout << "of Spades" << std::endl;
		break;
	case Club:
		std::cout << "of Clubs" << std::endl;
		break;
	case Heart:
		std::cout << "of Hearts" << std::endl;
		break;
	case Diamond:
		std::cout << "of Diamonds" << std::endl;
		break;
	}
}

int Card::getNumber(){
	return m_number;
}