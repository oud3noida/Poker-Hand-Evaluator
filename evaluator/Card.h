#ifndef POKER_HAND_EVALUATOR_CARD_H
#define POKER_HAND_EVALUATOR_CARD_H

#include <string>

using namespace std;

struct Card {
    /*
     * Store the number value and suit of a card as following:
     * Actual Number: 2 3 4 5 6 7 8 9 T  J  Q  K  A
     * Number Value:  1 2 3 4 5 6 7 8 9 10 11 12 13
     * Actual Suit:   s d h c
     * Suit Value:    0 1 2 3
     */

    int number, suit;
    string formatted;

    Card(string formatted);
    Card(int number, int suit);

    static int formatted_to_number(char c);

    static int formatted_to_suit(char c);

    static char number_to_formatted(int number);

    static char suit_to_formatted(int suit);
};


#endif //POKER_HAND_EVALUATOR_CARD_H
