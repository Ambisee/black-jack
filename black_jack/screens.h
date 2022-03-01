// screens.h :
// This file contains the function definition for displaying the different window screens
// in the program
//

# pragma once

# ifndef SCREENS_H
# define SCREENS_H

# include <iostream>
# include <string>
# include <random>
# include <vector>
# include "os_utils.h"
# include "utils.h"
# include "Option.h"
# include "Card.h"
# include "Bet.h"


const int main_menu_quit_conf_number = 3;
const int option_quit_conf_number = 4;
const int rounds_to_shuffle = 4;
const std::string header =
" _     _            _    _            _    \n"
"| |   | |          | |  (_)          | |   \n"
"| |__ | | __ _  ___| | ___  __ _  ___| | __\n"
"| '_ \\| |/ _` |/ __| |/ / |/ _` |/ __| |/ /\n"
"| |_) | | (_| | (__|   <| | (_| | (__|   < \n"
"|_.__/|_|\\__,_|\\___|_|\\_\\ |\\__,_|\\___|_|\\_\\\n"
"                       _/ |                \n"
"                      |__/                 \n";


// main_menu_screen(): 
// Display for the main menu and handles the reception of the user's choice
// @params :
// No parameters
// @returns :
// selection: int = user's choice on where to navigate
int main_menu_screen();


// option_screen(): 
// Display the options menu
// @params :
// - gameOptions: Option* = the pointer to the object that will store the configuration
// @return :
// No return value
//
void option_screen(Option* gameOptions);


// game_screen(): 
// Display the game screen
// @params :
// - gameOptions: Option* = the pointer to the object that will store the configuration
// @return :
// No return values
void game_screen(Option* gameOptions);


// round_screen(): 
// Display one round of the betting
// @params :
// - current_bet: Bet = player's current bet
// - player_balance: int = player's current balance
// - player_hand: std::vector<Card> = player's hand
// - house_hand: std::vector<Card> = house's hand
// - split_hand: Card = the variable that stores
// @return :
// - continue_bet: bool = a boolean value indicating whether or not there's another bet
bool round_screen(
	int& player_balance,
	Bet& current_bet,
	std::vector<Card>& deck,
	std::vector<Card>& player_hand,
	std::vector<Card>& house_hand,
	Card& split_hand
);

# endif