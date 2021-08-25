#include "Card.h"
#include <cassert>

using namespace std;

Card::Card(string formatted) {
    assert(formatted.length() == 2);
    this->formatted = formatted;
    this->number = formatted_to_number(formatted[0]);
    this->suit = formatted_to_suit(formatted[1]);
}

Card::Card(int number, int suit) {
    this->number = number;
    this->suit = suit;
    this->formatted = string() + number_to_formatted(number) + suit_to_formatted(suit);
}

int Card::formatted_to_number(char c) {
    switch (c) {
        case 'T': return 9;
        case 'J': return 10;
        case 'Q': return 11;
        case 'K': return 12;
        case 'A': return 13;
        default: return (c - '1');
    }
}

int Card::formatted_to_suit(char c) {
    switch (c) {
        case 's': return 0;
        case 'd': return 1;
        case 'h': return 2;
        case 'c': return 3;
    }
    assert(false);
    return -1;
}

char Card::number_to_formatted(int number) {
    switch (number) {
        case 9: return 'T';
        case 10: return 'J';
        case 11: return 'Q';
        case 12: return 'K';
        case 13: return 'A';
        default: return (char) (number + '1');
    }
}

char Card::suit_to_formatted(int suit) {
    assert(0 <= suit && suit < 4);
    switch (suit) {
        case 0: return 's';
        case 1: return 'd';
        case 2: return 'h';
        case 3: return 'c';
    }
    return ' ';
}