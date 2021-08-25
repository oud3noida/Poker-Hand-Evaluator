#include "Evaluator.h"
#include <cassert>
#include <iostream>
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
    bitset<7> b(index_bits);
    cerr << b.to_string() << endl;
    return index_bits;
}