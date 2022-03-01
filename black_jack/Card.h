// Card.h :
// This file contains the interface for the Card class

# pragma once

# ifndef CARD_H
# define CARD_H

# include <iostream>
# include <string>
# include <array>

class Card {
private:
	std::string rank;
	std::string suit;
public:
	// Static variables
	static std::array<std::string, 13> ranks;
	static std::array<std::string, 4> suits;

	// Constructors
	Card();
	Card(std::string rank, std::string suit);

	// Setters
	void set_rank(std::string new_rank);
	void set_suit(std::string new_suit);

	// Getters
	std::string get_rank();
	std::string get_suit();
	int get_value();

	// Destructor
	~Card();
};

# endif

