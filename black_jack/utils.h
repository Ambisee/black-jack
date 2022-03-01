// utils.h :
// This file contains helper functions for the game
//

# pragma once

# ifndef UTILS_H
# define UTILS_H

# include <iostream>
# include <chrono>
# include <thread>
# include <string>
# include <random>
# include <ctime>
# include <cmath>
# include <vector>
# include "Bet.h"
# include "Card.h"
# include "os_utils.h"

namespace utils {
    // sleep(): 
    // Sleep for a certain amount of time
    // @params :
    // - milliseconds: int = amount of time to sleep in milliseconds
    // @return :
    // No return value
    void sleep(int milliseconds);


    // ask_player_betting_amount():
    // Ask the player for a betting amount
    // @params :
    // - player_balance: int = the player's current balance
    // @return :
    // - amount: int = the amount of money the player wants to bet;
    int ask_player_betting_amount(int& player_balance);


    // clear_console_input()
    // Helper function to flush out the input stream
    // @params :
    // No parameters
    // @return :
    // No return value
    void clear_console_input();
    
    
    // initialize_random_seed(): 
    // Intialize the seed needed for functions in the random header file
    // @params :
    // No parameters
    // @return :
    // No return value
    void initialize_random_seed();


    // generate_cards(): 
    // Generate standard 52 decks of cards and return a vector
    // @params :
    // - num_of_deck: int = the number of decks to generate
    // @return :
    // An array of Card object representing a standard 52 deck of cards
    std::vector<Card> generate_deck(int num_of_deck = 1);


    // shuffle_cards(): 
    // Shuffle the given deck
    // @params :
    // - deck: std::vector<Card> = the deck of cards to be shuffled
    // @return :
    // No return value
    void shuffle_cards(std::vector<Card>& deck);


    // calculate_total_value(): 
    // Calculate the total value of in a hand
    // @params :
    // - hand: std::vector<Card> = a set of cards whose value is to be calculated
    // @return :
    // - value: int = the calculated total value;
    int calculate_total_value(std::vector<Card>& hand, int start = 0);


    // select_card(): 
    // Pick the card at the top of the deck
    // @params :
    // - deck: std::vector<Card> = the deck of cards to be shuffled
    // - hand: std::vector<Card> = the target hand to put the selected card
    // @return :
    // No return value
    void select_card(std::vector<Card>& deck, std::vector<Card>& hand);


    // ask_player_decision(): 
    // Ask the player for their decision for the current round of decision and validate 
    // that they can only choose the options that are possible
    // @params :
    // - betting_amount: int = the amount the player is betting
    // - player_balance: int = player's current balance
    // - player_hand: std::vector<Card> = player's current hand
    // - house_hand: std::vector<Card> = house's current hand
    // @return :
    // decision: int = an integer representing the player's decision
    int ask_player_decision(
        int betting_amount,
        int player_balance,
        std::vector<Card>& player_hand,
        std::vector<Card>& house_hand
    );

    // display_cards()
    // Display the name of the player, the cards they hold and their value
    // @params:
    // - name: std::string = the name of the player
    // - cards: std::vector<Card> = the cards that he or she has
    // - start: int = the first index from which the value of the cards is calculated
    // @return:
    // No return value
    void display_cards(
        std::string name,
        std::vector<Card>& cards,
        int start = 0
    );


    // display_initial_info(): 
    // Display the information on the screen
    // @params :
    // - player_balance: int = the player's current balance
    // - betting_amount: int = the amount that the player has bet
    // - house_hand: std::vector<Card> = the house's cards
    // - player_bet: Bet = the player's current round of betting
    // @return :
    // No return value
    void display_initial_info(
        int& player_balance,
        int betting_amount,
        std::vector<Card>& house_hand,
        std::vector<Card>& player_hand
    );
}

# endif