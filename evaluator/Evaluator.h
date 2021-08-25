#ifndef POKER_HAND_EVALUATOR_EVALUATOR_H
#define POKER_HAND_EVALUATOR_EVALUATOR_H

#include "Card.h"
#include <vector>

using namespace std;

class Evaluator {
private:
    vector<Card> cards;

public:
    explicit Evaluator(vector<Card> &cards);

    int evaluate();

    int evaluate_5(int index_bits);
};


#endif //POKER_HAND_EVALUATOR_EVALUATOR_H
