// Option.h :
// This file contains the interface for the Option class
//

# pragma once

# ifndef OPTION_H
# define OPTION_H

# include <iostream>


class Option {
private:
	int starting_amount;
	int number_of_coms;
public:
	// Constructors
	Option();
		// Default constructor
	Option(int amount, int number_of_coms);
		// Parameterized constructor

	// Setter
	void set_starting_amount(int amount);
		// Set the starting amount of money for the player
	void set_number_of_coms(int new_num);
		// Set the number of computer players that will compete with the player

	// Getter
	int get_starting_amount();
		// Get the starting amount of money for the player
	int get_number_of_coms();
		// Get the number of computer players that will compete with the player

	// Destructor
	~Option();	
};

# endif