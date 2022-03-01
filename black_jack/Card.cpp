// Card.cpp
// This file contains the implementation for the Card class

# include <iostream>
# include <string>
# include <array>
# include "Card.h"

std::array<std::string, 13> Card::ranks {
		"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};
std::array<std::string, 4> Card::suits {
	"S", "H", "D", "C"
};

Card::Card() : rank("A"), suit("S") {

}


Card::Card(std::string rank, std::string suit) : rank(rank), suit(suit) {

}


void Card::set_rank(std::string new_rank) {
	for (int i = 0; i < Card::ranks.size(); i++) {
		if (new_rank == Card::ranks[i]) {
			rank = new_rank;
			break;
		}
	}
}


void Card::set_suit(std::string new_suit) {
	switch (std::toupper(new_suit[0])) {
		case 'S':
			rank = "S";
			break;
		case 'H':
			rank = "H";
			break;
		case 'D':
			rank = "D";
			break;
		case 'C':
			rank = "C";
			break;
		default:
			break;
	}
}


std::string Card::get_rank() {
	return rank;
}


std::string Card::get_suit() {
	/*switch (rank[0]) {
		case 'S':
			return "\u2660";
			break;
		case 'H':
			return "\u2665";
			break;
		case 'D':
			return "\u2666";
			break;
		case 'C':
			return "\u2663";
			break;
		default:
			return "";
			break;
	}*/
	return suit;
}


int Card::get_value() {
	switch (toupper(rank[0])) {
		case 'A':
			return 11;
			break;
		case 'J':
			return 10;
			break;
		case 'Q':
			return 10;
			break;
		case 'K':
			return 10;
			break;
		default:
			break;
	}

	return atoi(rank.c_str());
}


Card::~Card() {

}