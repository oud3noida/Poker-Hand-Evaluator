#ifndef POKER_HAND_EVALUATOR_EVALUATOR_H
#define POKER_HAND_EVALUATOR_EVALUATOR_H

#include "Card.h"
#include <vector>
#include <map>

using namespace std;

class Evaluator {
private:
    vector<Card> cards;

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
    static constexpr int ONE_KICKER = 16,
                         TWO_KICKER = 16*16,
                         THREE_KICKER = 16*16*16,
                         FOUR_KICKER = 16*16*16*16,
                         FIVE_KICKER = 16*16*16*16*16;
    static constexpr int HIGH_CARD = 0,
                         ONE_PAIR = 1,
                         TWO_PAIR = 2,
                         THREE_OF_A_KIND = 3,
                         STRAIGHT = 4,
                         FLUSH = 5,
                         FULL_HOUSE = 6,
                         FOUR_OF_A_KIND = 7,
                         STRAIGHT_FLUSH = 8,
                         HAND_OF_HIGHEST_RANK = 9;
    static constexpr int HAND_BOUNDARY[10] = {
            0,
            FIVE_KICKER,
            FIVE_KICKER + FOUR_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER + ONE_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER + ONE_KICKER + FIVE_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER + ONE_KICKER + FIVE_KICKER + TWO_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER + ONE_KICKER + FIVE_KICKER + TWO_KICKER + TWO_KICKER,
            FIVE_KICKER + FOUR_KICKER + THREE_KICKER + THREE_KICKER + ONE_KICKER + FIVE_KICKER + TWO_KICKER + TWO_KICKER + FIVE_KICKER
    };

public:
    explicit Evaluator(vector<Card> &cards);

    int evaluate();

    int evaluate_5(int index_bits);

    bool is_straight(map<int, int> &unique_cards);

    int find_duplicate(map<int, int> &unique_cards, int card_count);

    int calculate_rank(map<int, int> &unique_cards);

    static string get_hand_name(int hand_rank);
};


#endif //POKER_HAND_EVALUATOR_EVALUATOR_H
