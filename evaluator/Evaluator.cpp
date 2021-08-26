#include "Evaluator.h"
#include <cassert>
#include <bitset>

using namespace std;

Evaluator::Evaluator(vector<Card> &cards) {
    this->cards = cards;
}

int Evaluator::evaluate() {
    int n = cards.size();
    assert(n >= 5);

    int index_bits = (1<<5) - 1;

    if (n == 5)
        return evaluate_5(index_bits);

    int ret = 0;
    while (index_bits < (1<<n)) {
        ret = max(ret, evaluate_5(index_bits));

        int lsb = index_bits & -index_bits;
        int leading_ones = index_bits + lsb;
        int trailing_one = ((index_bits & ~leading_ones) / lsb) >> 1;
        index_bits = leading_ones | trailing_one;
    }
    return ret;
}

int Evaluator::evaluate_5(int index_bits) {
    /*
     * The higher the value is, the higher the rank of the hand is
     *
     * 16^1 = 16
     * 16^2 = 256
     * 16^3 = 4096
     * 16^4 = 65536
     * 16^5 = 1048576
     *
     * 0. High card:       16^5
     * 1. One pair:        16^4
     * 2. Two pair:        16^3
     * 3. Three of a kind: 16^3
     * 4. Straight:        16^1
     * 5. Flush:           16^5
     * 6. Full house:      16^2
     * 7. Four of a kind:  16^2
     * 8. Straight Flush:  16^5
     */

    map<int, int> unique_cards;
    int unique_suits_bitwise = 0;
    for (int i = 0; i < cards.size(); ++i) {
        if (index_bits & (1 << i)) {
            if (unique_cards.find(cards[i].number) == unique_cards.end()) {
                unique_cards[cards[i].number] = 0;
            } else {
                ++unique_cards[cards[i].number];
            }
            unique_suits_bitwise |= (1 << cards[i].suit);
        }
    }

    bitset<4> unique_suits(unique_suits_bitwise);
    if (unique_suits.count() == 1) {
        // FLUSH
        switch (unique_cards.size()) {
            case 5: {
                if (is_straight(unique_cards)) {
                    // STRAIGHT FLUSH
                    if (unique_cards.begin()->second == Card::formatted_to_number('2') &&
                        prev(unique_cards.end())->second == Card::formatted_to_number('A')) {
                        return HAND_BOUNDARY[STRAIGHT_FLUSH];
                    } else {
                        return HAND_BOUNDARY[STRAIGHT_FLUSH] + unique_cards.begin()->first;
                    }
                }
            }
            default: {
                int flush_rank = HAND_BOUNDARY[FLUSH] + calculate_rank(unique_cards);
                assert(HAND_BOUNDARY[FLUSH] <= flush_rank && flush_rank < HAND_BOUNDARY[FLUSH + 1]);
                return flush_rank;
            }
        }
    } else {
        switch (unique_cards.size()) {
            case 5: {
                if (is_straight(unique_cards)) {
                    // STRAIGHT
                    if (unique_cards.begin()->second == Card::formatted_to_number('2') &&
                        unique_cards.rbegin()->second == Card::formatted_to_number('A')) {
                        return HAND_BOUNDARY[STRAIGHT];
                    } else {
                        return HAND_BOUNDARY[STRAIGHT] + unique_cards.begin()->first;
                    }
                } else {
                    // HIGH CARD
                    int high_card_rank = HAND_BOUNDARY[HIGH_CARD] + calculate_rank(unique_cards);
                    assert(HAND_BOUNDARY[HIGH_CARD] <= high_card_rank && high_card_rank < HAND_BOUNDARY[HIGH_CARD + 1]);
                    return high_card_rank;
                }
            }
            case 4: {
                // ONE PAIR
                int pair_number = find_duplicate(unique_cards, 2);
                int one_pair_rank = HAND_BOUNDARY[ONE_PAIR] + (pair_number << 4*3);
                unique_cards.erase(pair_number);
                one_pair_rank += calculate_rank(unique_cards);
                assert(HAND_BOUNDARY[ONE_PAIR] <= one_pair_rank && one_pair_rank < HAND_BOUNDARY[ONE_PAIR + 1]);
                return one_pair_rank;
            }
            case 3: {
                int triple_number = find_duplicate(unique_cards, 3);
                if (triple_number != -1) {
                    // THREE OF A KIND
                    int three_of_a_kind_rank = HAND_BOUNDARY[THREE_OF_A_KIND] + (triple_number << 4 * 2);
                    unique_cards.erase(triple_number);
                    three_of_a_kind_rank += calculate_rank(unique_cards);
                    assert(HAND_BOUNDARY[THREE_OF_A_KIND] <= three_of_a_kind_rank && three_of_a_kind_rank < HAND_BOUNDARY[THREE_OF_A_KIND + 1]);
                    return three_of_a_kind_rank;
                } else {
                    // TWO PAIR
                    int pair_number = find_duplicate(unique_cards, 2);
                    int two_pair_rank = HAND_BOUNDARY[TWO_PAIR] + (pair_number << 4*1);
                    unique_cards.erase(pair_number);
                    pair_number = find_duplicate(unique_cards, 2);
                    two_pair_rank += (pair_number << 4*2);
                    unique_cards.erase(pair_number);
                    two_pair_rank += calculate_rank(unique_cards);
                    assert(HAND_BOUNDARY[TWO_PAIR] <= two_pair_rank && two_pair_rank < HAND_BOUNDARY[TWO_PAIR + 1]);
                    return two_pair_rank;
                }
            }
            case 2: {
                int triple_number = find_duplicate(unique_cards, 3);
                if (triple_number != -1) {
                    // FULL HOUSE
                    int full_house_rank = HAND_BOUNDARY[FULL_HOUSE] + (triple_number << 4*1);
                    unique_cards.erase(triple_number);
                    full_house_rank += calculate_rank(unique_cards);
                    assert(HAND_BOUNDARY[FULL_HOUSE] <= full_house_rank && full_house_rank < HAND_BOUNDARY[FULL_HOUSE + 1]);
                    return full_house_rank;
                } else {
                    // FOUR OF A KIND
                    int quadruple_number = find_duplicate(unique_cards, 4);
                    int four_of_a_kind_rank = HAND_BOUNDARY[FOUR_OF_A_KIND] + (quadruple_number << 4*1);
                    unique_cards.erase(quadruple_number);
                    four_of_a_kind_rank += calculate_rank(unique_cards);
                    assert(HAND_BOUNDARY[FOUR_OF_A_KIND] <= four_of_a_kind_rank && four_of_a_kind_rank < HAND_BOUNDARY[FOUR_OF_A_KIND + 1]);
                    return four_of_a_kind_rank;
                }
            }
            default: {
                assert(false);
                return -1;
            }
        }
    }

    assert(false);
    return -1;
}

bool Evaluator::is_straight(map<int, int> &unique_cards) {
    assert(unique_cards.size() == 5);
    for (auto card = unique_cards.begin(); card != prev(unique_cards.end()); ++card) {
        if (card->first + 1 != next(card)->first &&
                !(card->first == Card::formatted_to_number('5') &&
                next(card)->first == Card::formatted_to_number('A'))) {
            return false;
        }
    }
    return true;
}

int Evaluator::find_duplicate(map<int, int> &unique_cards, int card_count) {
    for (auto card = unique_cards.begin(); card != prev(unique_cards.end()); ++card) {
        if (card->second == card_count) return card->first;
    }
    return -1;
}

int Evaluator::calculate_rank(map<int, int> &unique_cards) {
    int ret = 0;
    for (auto card = unique_cards.rbegin(); card != unique_cards.rend(); ++card) {
        ret <<= 4;
        ret += card->first;
    }
    return ret;
}

string Evaluator::get_hand_name(int hand_rank) {
    string hand_names[9] = {
            "HIGH CARD",
            "ONE PAIR",
            "TWO PAIR",
            "THREE OF A KIND",
            "STRAIGHT",
            "FLUSH",
            "FULL HOUSE",
            "FOUR OF A KIND",
            "STRAIGHT FLUSH"
    };

    for (int i = 0; i < 9; ++i) {
        if (hand_rank < HAND_BOUNDARY[i + 1]) return hand_names[i];
    }
    assert(false);
    return "ERR";
}