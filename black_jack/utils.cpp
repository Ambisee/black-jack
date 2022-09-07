// utils.cpp :
// This file contains the implementation for the helper functions for the game
//

# include <iostream>
# include <chrono>
# include <thread>
# include <string>
# include <random>
# include <ctime>
# include <cmath>
# include <vector>
# include <limits>
# include "os_utils.h"
# include "Card.h"
# include "Bet.h"

namespace utils {
    void sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }


    void clear_console_input() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    void initialize_random_seed() {
        std::srand(static_cast<unsigned int>(time(NULL)));
    }


    std::vector<Card> generate_deck(int num_of_deck = 1) {
        std::vector<Card> deck;

        for (int times = 0; times < num_of_deck; times++) {
            for (int i = 0; i < Card::suits.size(); i++) {
                for (int j = 0; j < Card::ranks.size(); j++) {
                    deck.push_back(Card(Card::ranks[j], Card::suits[i]));
                }
            }
        }

        return deck;
    }


    void shuffle_cards(std::vector<Card>& deck) {
        std::random_shuffle(deck.begin(), deck.end());
    }


    int calculate_total_value(std::vector<Card>& hand, int start = 0) {
        int num_of_aces = 0;
        int value = 0;

        for (int i = start; i < hand.size(); i++) {
            if (hand[i].get_rank() == "A") {
                num_of_aces++;
                continue;
            }
            value += hand[i].get_value();
        }

        value += std::max(0, num_of_aces - 1);
        if (num_of_aces > 0) {
            if (value + 11 <= 21) {
                value += 11;
            } else {
                value += 1;
            }
        }

        return value;
    }


    void select_card(std::vector<Card>& deck, std::vector<Card>& hand) {
        hand.insert(
            hand.begin(),
            deck[deck.size() - 1]
        );

        deck.erase(deck.end() - 1);
        //hand.push_back(deck[deck.size() - 1]);
        //deck.pop_back();
    }


    int ask_player_betting_amount(int& player_balance) {
        int amount = -1;

        while (amount < 0) {
            std::cout << "Enter an amount to bet (Your current amount: " << player_balance << ") : ";
            std::cin >> amount;

            /* Check if player input an integer */
            if (std::cin.fail()) {
                clear_console_input();
                os_utils::clrscr();
                continue;
            }

            /* Check if player's betting amount isn't negative and lower than player's balance */
            if (amount > player_balance) {
                clear_console_input();
                os_utils::clrscr();
                continue;
            }
        }

        return amount;
    }


    void display_cards(
        std::string name,
        std::vector<Card>& cards,
        int start = 0
    ) {
        std::cout << name << ": ";
        for (int i = 0; i < cards.size(); i++) {
            std::cout << ((i < start) ? "??" : (cards[i].get_rank() + cards[i].get_suit())) << " ";
        }
        std::cout << "- " << utils::calculate_total_value(cards, start);
    }


    void display_initial_info(
        int& player_balance,
        int betting_amount,
        std::vector<Card>& house_hand,
        std::vector<Card>& player_hand
    ) {
        // Display player's balance and the amount they bet
        std::cout << "Player's current balance: " << player_balance << "\n"
            << "Amount bet: " << betting_amount << "\n";

        // Display information on the house's cards
        utils::display_cards("House", house_hand, 1);
        std::cout << '\n';

        // Display information on the player's cards
        utils::display_cards("Player", player_hand, 0);
    }


    int ask_player_decision(
        int betting_amount,
        int player_balance,
        std::vector<Card>& player_hand,
        std::vector<Card>& house_hand
    ) {
        int decision = 0;
        bool can_double = (player_balance >= betting_amount && player_hand.size() == 2);
        bool can_split = (
            player_hand.size() == 2 &&
            player_hand[0].get_value() == player_hand[1].get_value()
        );

        os_utils::clrscr();

        while (decision == 0) {
            utils::display_initial_info(player_balance, betting_amount, house_hand, player_hand);
            std::cout << '\n';
            std::cout << "[1] Hit" << "\n"
                << "[2] Stand" << "\n";

            if (can_double) {
                std::cout << "[3] Double" << "\n";
            }
            if (can_split) {
                std::cout << "[4] Split" << "\n";
            }

            std::cout << "Select your options : ";
            std::cin >> decision;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                os_utils::clrscr();
            } else if ((!(can_double) && decision == 3) || (!(can_split) && decision == 4)) {
                decision = 0;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                os_utils::clrscr();
            }
        }

        os_utils::clrscr();
        return decision;
    }
}