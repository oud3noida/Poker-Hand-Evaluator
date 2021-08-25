#include <iostream>
#include "evaluator/Evaluator.h"

using namespace std;

int main() {
    vector<Card> cards(7, Card("2s"));
    Evaluator ev(cards);
    ev.evaluate();
}