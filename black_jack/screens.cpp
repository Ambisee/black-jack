// screens.h :
// This file contains the function implementation for displaying the different window screens
// in the program
//

# pragma once

# include <iostream>
# include <string>
# include <random>
# include "os_utils.h"
# include "screens.h"
# include "utils.h"
# include "Option.h"
# include "Card.h"
# include "Bet.h"


int main_menu_screen() {
	int selection = 0;
	while ((selection < 1) || (selection > main_menu_quit_conf_number)) {
		// Blackjack header
		std::cout << header << "\n"
			// Show options
			<< "[1] Play" << "\n"
			<< "[2] Options" << "\n"
			<< "[3] Quit" << "\n"
			<< "Choose a number : ";
		std::cin >> selection;

		// Check if the user entered a valid integer
		if (std::cin.fail()) {
			utils::clear_console_input();
			selection = 0;
		}
		os_utils::clrscr();
	}
	return selection;
}


void option_screen(Option* gameOptions) {
	bool run = true;
	int conf_number = 0;
	int value = 0;

	while (run) {
		std::cout << "---OPTIONS---" << "\n"
			<< "[1] Initial balance (current : " << gameOptions->get_starting_amount() << ")" << "\n"
			<< "[2] Number of COMs (current : " << gameOptions->get_number_of_coms() << ")" << "\n"
			<< "[3] Reset to default" << "\n"
			<< "[4] Back" << "\n"
			<< "Type in a command in the FORMAT {conf_number} { value } OR INPUT A NUMBER to change the configuration : ";

		std::cin >> conf_number;
		if (std::cin.fail()) {
			utils::clear_console_input();
			os_utils::clrscr();
			continue;
		}

		if (conf_number == option_quit_conf_number) {
			os_utils::clrscr();
			break;
		}
		if ((conf_number < 1) || (conf_number > option_quit_conf_number)) {
			os_utils::clrscr();
			continue;
		}

		os_utils::clrscr();
		std::cout << "Enter a new value for the config : ";
		switch (conf_number) {
			case 1:
				std::cout << "starting amount = ";
				break;
			case 2:
				std::cout << "number of COMs = ";
				break;
			case 3:
				gameOptions->set_starting_amount(1000);
				gameOptions->set_number_of_coms(0);
				os_utils::clrscr();
				continue;
			default:
				std::cout << "ERROR = ";
				break;
		}

		std::cin >> value;
		if (std::cin.fail()) {
			utils::clear_console_input();
			os_utils::clrscr();
			continue;
		}

		switch (conf_number) {
			case 1:
				gameOptions->set_starting_amount(value);
				break;
			case 2:
				gameOptions->set_number_of_coms(value);
				break;
			default:
				break;
		}
		os_utils::clrscr();
	}
}


void game_screen(Option* gameOptions) {
	int player_balance = gameOptions->get_starting_amount();
	int betting_amount = 0;
	int bet_round = 0;
	int game_round = 0;

	bool run = true;
	bool continue_round = true;

	std::vector<Bet> player_bets;
	std::vector<Card> player_hand;
	std::vector<Card> house_hand;
	std::vector<Card> deck = utils::generate_deck(2);

	utils::initialize_random_seed();
	utils::shuffle_cards(deck);

	while (run || player_balance <= 0) {
		Card split_card;

		// Shuffle the deck if it reaches a certain number of rounds
		if (game_round % rounds_to_shuffle == 0) {
			deck.clear();
			deck = utils::generate_deck(2);
			utils::shuffle_cards(deck);
		}

		int betting_amount = utils::ask_player_betting_amount(player_balance);
		
		if (betting_amount == 0) {
			os_utils::clrscr();
			break;
		}

		player_balance -= betting_amount;

		// Distributing the cards to the players
		for (int i = 0; i < 2; i++) {
			utils::select_card(deck, player_hand);
			utils::select_card(deck, house_hand);
		}

		player_bets.push_back(Bet(betting_amount, 0, false));
		continue_round = round_screen(
			player_balance,
			player_bets[bet_round],
			deck,
			player_hand,
			house_hand,
			split_card
		);

		while (continue_round) {
			player_hand.clear();
			player_hand.push_back(split_card);
			utils::select_card(deck, player_hand);
			player_bets.push_back(Bet(betting_amount, 0, false));
			bet_round++;

			continue_round = round_screen(
				player_balance,
				player_bets[bet_round],
				deck,
				player_hand,
				house_hand,
				split_card
			);
		}

		os_utils::clrscr();

		// House logic for evaluating when to select card
		while (utils::calculate_total_value(house_hand) < 15) {
			utils::select_card(deck, house_hand);
		}

		int house_val = utils::calculate_total_value(house_hand);

		// Calculate winnings
		utils::display_cards("House", house_hand, 0);
		std::cout << '\n';

		for (Bet bet : player_bets) {
			utils::display_cards("Bet", bet.get_cards(), 0);
			if (bet.get_card_value() <= 21) {
				// Check for blackjack
				if ((bet.get_card_value() > house_val) || house_val > 21) {
					if (bet.is_blackjack()) {
						player_balance += static_cast<int>(2.5 * bet.get_betting_amount());
						std::cout << " - BJ\n";
					} else {
						player_balance += (2 * bet.get_betting_amount());
						std::cout << " - Win\n";
					}
				// Check for draw
				} else if (house_val == bet.get_card_value()) {
					player_balance += bet.get_betting_amount();
					std::cout << " - Draw\n";
				} else {
					std::cout << " - Lost\n";
				}
			} else {
				std::cout << " - Lost\n";
			}
		}

		// Resets
		player_bets.clear();
		player_hand.clear();
		house_hand.clear();
		bet_round = 0;
		game_round++;
	}

	os_utils::clrscr();
}


bool round_screen(
	int& player_balance,
	Bet& current_bet,
	std::vector<Card>& deck,
	std::vector<Card>& player_hand,
	std::vector<Card>& house_hand,
	Card& split_hand
) {
	int decision = 0;
	int round = 0;
	bool did_split = false;
	bool can_split = (player_hand.size() == 2 && (player_hand[0].get_value() == player_hand[1].get_value()));
	bool can_double = (player_balance >= current_bet.get_betting_amount());

	os_utils::clrscr();

	// Check if player has a blackjack / busted / decided to stand
	while (
		(utils::calculate_total_value(player_hand) < 21)
	) {
		// Ask for user to decide next step
		decision = utils::ask_player_decision(
			current_bet.get_betting_amount(),
			player_balance,
			player_hand,
			house_hand
		);

		// Decision processing
		switch (decision) {
			// Hit
			case 1:
				utils::select_card(deck, player_hand);
				current_bet.set_card_value(utils::calculate_total_value(player_hand));
				current_bet.set_cards(player_hand);
				break;
			// Stand
			case 2:
				current_bet.set_cards(player_hand);
				current_bet.set_card_value(utils::calculate_total_value(player_hand));
				return did_split;
			// Double
			case 3:
				player_balance -= current_bet.get_betting_amount();
				utils::select_card(deck, player_hand);
				current_bet.set_betting_amount(current_bet.get_betting_amount() * 2); 
				current_bet.set_card_value(utils::calculate_total_value(player_hand));
				current_bet.set_cards(player_hand);
				return did_split;
			// Split
			case 4:
				split_hand = player_hand[1];
				player_hand.pop_back();
				utils::select_card(deck, player_hand);
				current_bet.set_card_value(utils::calculate_total_value(player_hand));
				did_split = true;
				break;
			default:
				break;
		}

		round++;
		decision = 0;
		os_utils::clrscr();
	}

	if (round == 0 && utils::calculate_total_value(player_hand) == 21) {
		current_bet.set_blackjack(true);
		current_bet.set_cards(player_hand);
		current_bet.set_card_value(21);
	}

	os_utils::clrscr();
	return did_split;
}