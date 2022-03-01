// Bet.cpp
// This file contains the implementation for the Bet class

# include <iostream>
# include <vector>
# include <string>
# include <map>
# include "Bet.h"
# include "utils.h"


Bet::Bet(): betting_amount(0), card_value(0), blackjack(false) {
	cards = {};
}


Bet::Bet(int init_betting_amount, int init_card_value, bool blackjack) :
	betting_amount(init_betting_amount),
	card_value(init_card_value),
	blackjack(blackjack)
{

}


Bet::Bet(int init_betting_amount, int init_card_value, bool blackjack, std::vector<Card>& cards):
	betting_amount(init_betting_amount),
	card_value(init_card_value),
	blackjack(blackjack),
	cards(cards)
{
	
}


std::vector<Card>& Bet::get_cards() {
	return cards;
}

int Bet::get_betting_amount() {
	return betting_amount;
}


int Bet::get_card_value() {
	return card_value;
}


bool Bet::is_blackjack() {
	return blackjack;
}


void Bet::set_betting_amount(int new_amount) {
	betting_amount = new_amount;
}


void Bet::set_card_value(int new_value) {
	card_value = new_value;
}


void Bet::set_blackjack(bool new_blackjack) {
	blackjack = new_blackjack;
}


void Bet::set_cards(std::vector<Card>& new_cards) {
	cards = new_cards;
}


Bet::~Bet() {

}