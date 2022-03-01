// Option.cpp
// This file contains the implementation for the Option class
//

# include <iostream>
# include "Option.h"

Option::Option() : starting_amount(1000), number_of_coms(0) {

}

Option::Option(int amount, int number_of_coms) : starting_amount(amount), number_of_coms(number_of_coms) {

}

void Option::set_number_of_coms(int new_num) {
	number_of_coms = new_num;
}

void Option::set_starting_amount(int new_amount) {
	starting_amount = new_amount;
}

int Option::get_starting_amount() {
	return starting_amount;
}

int Option::get_number_of_coms() {
	return number_of_coms;
}

Option::~Option() {

}