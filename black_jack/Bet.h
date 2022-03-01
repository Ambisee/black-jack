// Bet.h
// This file contains the interface for the Bet class
//

# ifndef BET_H
# define BET_H
# pragma once

# include <iostream>
# include <string>
# include <vector>
# include <array>
# include <map>
# include "Card.h"

class Bet {
private:
	int betting_amount;
	int card_value;
	bool blackjack;

	std::vector<Card> cards;

public:
	// Constructors
	Bet();
	Bet(
		int betting_amount,
		int card_value,
		bool blackjack
	);
	Bet(
		int betting_amount,
		int card_value,
		bool blackjack,
		std::vector<Card>& cards
	);

	// Getters
	std::vector<Card>& get_cards();
	int get_betting_amount();
	int get_card_value();
	bool is_blackjack();

	// Setters
	void set_betting_amount(int new_amount);
	void set_card_value(int new_value);
	void set_blackjack(bool new_blackjack);
	void set_cards(std::vector<Card>& new_cards);

	// Destructors
	~Bet();
};

# endif